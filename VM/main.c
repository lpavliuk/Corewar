/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 14:03:16 by tkiselev          #+#    #+#             */
/*   Updated: 2018/07/19 14:03:20 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>
/*
** start STAFF
*/

t_vm		*init_vm(void)
{
	t_vm	*new;

	if (!(new = (t_vm *)malloc(sizeof(t_vm))))
		exit(0);
	ft_bzero(new->map, MEM_SIZE);
	new->flag_dump = 0;
	new->nbr_cycles = 0;
	new->count_players = 0;
	new->bot = NULL;
	return (new);
}

void		usage(void)
{
	ft_printf("USAGE\n");
	exit(0);
}

void		ft_error(char *s)
{
	ft_printf("%s\n", s);
	exit(0);
}

/*
** end STAFF
*/

t_bot		*push_new_bot(t_bot **head, unsigned int player)
{
	t_bot	*new;
	t_bot	*tmp;

	tmp = *head;
	while (tmp && tmp->next)
	{
		(tmp->player == player) ? ft_error("Error") : 0;
		tmp = tmp->next;
	}
	new = (t_bot *)malloc(sizeof(t_bot));
	(!new) ? ft_error("Error") : 0;
	new->player = player;
	ft_bzero(new->name, PROG_NAME_LENGTH + 1);
	ft_bzero(new->comment, COMMENT_LENGTH + 1);
	new->exec = NULL;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
		tmp->next = new;
	return (new);
}

void		get_dump(t_vm *vm, char **args, int count, int *i)
{
	(*i)++;
	if (*i < count && ft_is_uint(args[*i]))
	{
		vm->flag_dump = 1;
		vm->nbr_cycles = ft_atoi(args[*i]);
	}
	else
		usage();
}

unsigned int	reverse_bytes(unsigned int data, char bytes)
{
	unsigned int res;

	res = data;
	if (bytes == 4)
	{
		((unsigned char *)&res)[0] = ((unsigned char *)&data)[3];
		((unsigned char *)&res)[1] = ((unsigned char *)&data)[2];
		((unsigned char *)&res)[2] = ((unsigned char *)&data)[1];
		((unsigned char *)&res)[3] = ((unsigned char *)&data)[0];
	}
	else if (bytes == 2)
	{
		((unsigned char *)&res)[0] = ((unsigned char *)&data)[1];
		((unsigned char *)&res)[1] = ((unsigned char *)&data)[0];
	}
	return (res);
}

void		check_magic_header(int fd)
{
	unsigned int	magic_header;

	if (read(fd, &magic_header, 4) != 4)
		ft_error("Error");
	magic_header = reverse_bytes(magic_header, 4);
	if (magic_header != COREWAR_EXEC_MAGIC)
		ft_error("Error");
}

void		get_name(int fd, t_bot *new)
{
	unsigned char	buf[4];
	char		i;

	if (read(fd, &new->name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
		ft_error("Error");
	if (read(fd, &buf, 4) != 4)
		ft_error("Error");
	i = 4;
	while (--i >= 0)
		if (buf[i] != 0)
			ft_error("Error");
}

void		get_size(int fd, t_bot *new)
{
	if (read(fd, &new->size, 4) != 4)
		ft_error("Error");
	new->size = reverse_bytes(new->size, 4);
	if (new->size > CHAMP_MAX_SIZE)
		ft_error("Error");
}

void		get_comment(int fd, t_bot *new)
{
	unsigned char	buf[4];
	char		i;

	if (read(fd, &new->comment, COMMENT_LENGTH) != COMMENT_LENGTH)
		ft_error("Error");
	if (read(fd, &buf, 4) != 4)
		ft_error("Error");
	i = 4;
	while (--i >= 0)
		if (buf[i] != 0)
			ft_error("Error");
}

void		get_executable(int fd, t_bot *new)
{
	unsigned char tmp[1];

	new->exec = (unsigned char *)malloc(new->size + 1);
	if (!new->exec)
		ft_error("Error");
	if (read(fd, new->exec, new->size) != new->size)
		ft_error("Error");
	
	if (read(fd, &tmp, 1) != 0)
		ft_error("Error");
}

/*
** Here I make bit-by-bit operation & for the last two bits in codage,
** as you may have guessed, with the number of 192 (128 + 64),
** and check whether these bits are on / off.
** After that I make a bitwise shift left on two bits.
*/

char		*decipher_codage(unsigned char codage)
{
	char		*arr;
	int		i;
	unsigned char	tmp;

	i = 0;
	(!(arr = (char *)ft_memalloc(4))) ? ft_error("Error") : 0;
	while (codage)
	{
		(i == 3) ? ft_error("Error") : 0;
		tmp = codage & 192;
		(tmp == 192) ? (arr[i] = IND_CODE) : 0;
		(tmp == 128) ? (arr[i] = DIR_CODE) : 0;
		(tmp == 64) ? (arr[i] = REG_CODE) : 0;
		(tmp == 0) ? ft_error("Error") : 0;
		codage <<= 2;
		i++;
	}
	return (arr);
}

/*
** This is the function that makes an array of types
** which must be presented after particular opcode,
** however such a function doesn't have at it's disposal
** such thing as codage.
*/

char		*pseudo_codage(char opcode)
{
	char	*arr;
	char	i;
	char	j;

	i = 3;
	(!(arr = (char *)ft_memalloc(4))) ? ft_error("Error") : 0;
	while (--i >= 0)
	{
		j = 3;
		while (--j >= 0)
		{
			if (ARG(opcode, i, j))
			{
				arr[i] = j + 1;
				break ;
			}
		}
	}
	return (arr);
}

void		check_arguments(char opcode, char *types, t_bot *bot, int *i)
{
	char	count;

	count = 0;
	while (types[count])
	{
		if (types[count] == REG_CODE)
		{
			if (*i >= bot->size || bot->exec[*i] > REG_NUMBER)
				ft_error("Error");
			*i += T_REG_SIZE;
		}
		else if (types[count] == IND_CODE)
		{
			if ((*i + 1) >= bot->size)
				ft_error("Error");
			*i += T_DIR_SIZE;
		}
		else if (types[count] == DIR_CODE)
		{
			if ((*i + LABEL_SIZE(opcode) - 1) >= bot->size)
				ft_error("Error");
			*i += LABEL_SIZE(opcode);
		}
		count++;
	}
}

void		check_command(t_bot *new, int *i)
{
	char	*codage;
	char	opcode;

	opcode = new->exec[*i];
	(*i)++;
	if (CODAGE(opcode))
	{
		(new->exec[*i] == '\0') ? ft_error("Error") : 0;
		codage = decipher_codage(new->exec[*i]);
		(*i)++;
	}
	else
		codage = pseudo_codage(opcode);
	check_arguments(opcode, codage, new, i);
	ft_strdel(&codage);
}

void		check_executable(t_bot *bot)
{
	int	i;

	i = 0;
	while (i < bot->size)
	{
		if (bot->exec[i] > 0 && bot->exec[i] <= MAX_TABLE)
			check_command(bot, &i);
		else
			ft_error("Error");
	}
}

/*
** This function makes a copy of an original executable of file,
** with reversed bytes.
*/

// unsigned char		*reverse_exec(t_bot *bot)
// {
// 	unsigned char	*new_exec;
// 	int				i;

// 	new_exec = (unsigned char *)ft_memalloc(bot->size + 1);
// 	(!new_exec) ? ft_error("Error") : 0;
// 	i = 0;
// 	while (i < bot->size)
// 	{
		
// 	}
// 	return (new_exec);
// }

char			get_arg_size(char opcode, char type)
{
	if (type == REG_CODE)
		return (T_REG_SIZE);
	else if (type == IND_CODE)
		return (T_IND_SIZE);
	else
	{
		if (LABEL_SIZE(opcode) == 4)
			return (4);
		else
			return (T_DIR_SIZE);
	}
}

char		*my_strsub(void *src, int start, int end)
{
	char	*s;
	int		i;
	int		size;

	size = end - start;
	if (!(s = (char *)malloc(size + 1)))
		ft_error("Error");
	ft_bzero(s, size + 1);
	i = 0;
	while (i < size)
	{
		s[i] = ((char *)src)[start + i];
		i++;
	}
	return (s);
}

unsigned int		get_arg(unsigned char *src, char size)
{
	unsigned int	res;

	res = 0;

	return (res);
}
unsigned char		**get_arguments(char opcode, char *types, unsigned char *src)
{
	unsigned char	**arguments;
	char			args_counter;
	char			i;
	char			arg_size;

	args_counter = ft_strlen(types);
	arguments = (unsigned char **)malloc(sizeof(unsigned char *) * (args_counter + 1));
	arguments[args_counter] = NULL;
	args_counter = 0;
	i = 0;
	while (types[args_counter])
	{
		arg_size = get_arg_size(opcode, types[args_counter]);
		args_counter++;
	}
	return (arguments);
}

void				add_block(t_bot *bot, unsigned char *new_exec, int *i)
{
	unsigned char	**arguments;
	char			opcode;
	char			*types;
	char			args_counter;

	opcode = bot->exec[*i];
	new_exec[(*i)++] = opcode;
	if (CODAGE(opcode))
	{
		types = decipher_codage(bot->exec[*i]);
		new_exec[*i] = bot->exec[*i];
		(*i)++;
	}
	else
		types = pseudo_codage(opcode);
	arguments = get_arguments(opcode, types, bot->exec + *i);
}

unsigned char		*reverse_exec(t_bot *bot)
{
	unsigned char	*new_exec;
	int				i;

	new_exec = (unsigned char *)ft_memalloc(bot->size + 1);
	(!new_exec) ? ft_error("Error") : 0;
	i = 0;
	while (i < bot->size)
		add_block(bot, new_exec, &i);
	return (new_exec);
}

void		bot_parsing(int fd, t_bot *new)
{
	unsigned char	*tmp;

	check_magic_header(fd);
	get_name(fd, new);
	get_size(fd, new);
	get_comment(fd, new);
	get_executable(fd, new);
	check_executable(new);
	tmp = reverse_exec(new);
	ft_strdel(&new->exec);
	new->exec = tmp;
}

void		get_bot(t_vm *vm, unsigned int player, char *filename)
{
	int		fd;
	t_bot		*new;

	vm->count_players++;	
	if (vm->count_players > 4)
		ft_error("Error");
	new = push_new_bot(&vm->bot, player);
	if ((fd = open(filename, O_RDONLY)) < 0 || read(fd, 0, 0) == -1)
		ft_error("Error");
	bot_parsing(fd, new);
	close(fd);
}

void		get_number_bot(t_vm *vm, char **args, int count, int *i)
{
	unsigned int	player;

	(*i)++;
	if (*i < count && ft_is_uint(args[*i]))
	{
		player = ft_atoi(args[*i]);
		(player > 4 || player == 0) ? ft_error("Error") : (*i)++;
		(*i < count) ? get_bot(vm, player, args[*i]) : usage();
	}
	else
		usage();
}

void		get_args(t_vm *vm, int count, char **args)
{
	int		i;
	unsigned int	player;

	player = 0;
	i = 1;
	while (i < count)
	{
		if (ft_strequ(args[i], "-dump"))
			get_dump(vm, args, count, &i);
		else if (ft_strequ(args[i], "-n"))
			get_number_bot(vm, args, count, &i);
		else
		{
			player--;
			get_bot(vm, player, args[i]);
		}
		i++;
	}
}

int			main(int ac, char **av)
{
	t_vm		*vm;

	if (ac > 1)
	{
		vm = init_vm();
		get_args(vm, ac, av);
	}
	else
		usage();
	return (0);
}
