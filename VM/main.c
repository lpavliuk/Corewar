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

t_vm		*init_vm(void)
{
	t_vm	*new;

	if (!(new = (t_vm *)malloc(sizeof(t_vm))))
		exit(0);
	ft_bzero(g_map, MEM_SIZE);
	new->count_players = 0;
	new->flag_visual = 0;
	new->flag_dump = 0;
	new->flag_server = 0;
	new->flag_client = 0;
	new->cycle_to_die = CYCLE_TO_DIE;
	new->nbr_cycles = 0;
	new->cur_cycle = 0;
	new->process_count = 0;
	vm->port = 0;
	new->ip = NULL;
	new->winner = NULL;
	new->process = NULL;
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

t_bot		*bot_init(unsigned int id, unsigned char player_counter)
{
	t_bot	*new;

	new = (t_bot *)malloc(sizeof(t_bot));
	(!new) ? ft_error("Error") : 0;
	new->player_counter = player_counter;
	ft_bzero(new->name, PROG_NAME_LENGTH + 1);
	ft_bzero(new->comment, COMMENT_LENGTH + 1);
	new->exec = NULL;
	new->id = id;
	new->size = 0;
	new->lives_whole = 0;
	new->lives_cur_period = 0;
	new->lives_last_period = 0;
	new->last_live = 0;
	new->next = NULL;
	return (new);
}

t_bot		*push_new_bot(t_bot **head, unsigned int id)
{
	unsigned char	player_counter;
	t_bot			*tmp;
	t_bot			*new;

	player_counter = 1;
	tmp = *head;
	while (tmp)
	{
		player_counter++;
		if (tmp->id == id)
			ft_error("Error");
		else if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	new = bot_init(id, player_counter);
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
	unsigned char	i;

	if (read(fd, &new->name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
		ft_error("Error");
	if (read(fd, &buf, 4) != 4)
		ft_error("Error");
	i = 0;
	while (i < 4)
		(buf[i] != 0) ? ft_error("Error") : i++;
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
	unsigned char	i;

	if (read(fd, &new->comment, COMMENT_LENGTH) != COMMENT_LENGTH)
		ft_error("Error");
	if (read(fd, &buf, 4) != 4)
		ft_error("Error");
	i = 0;
	while (i < 4)
		(buf[i] != 0) ? ft_error("Error") : i++;
}

void		get_executable(int fd, t_bot *new)
{
	unsigned char tmp[1];

	new->exec = (unsigned char *)malloc(new->size + 1);
	if (!new->exec)
		ft_error("Error");
	if (read(fd, new->exec, new->size) != new->size)
		ft_error("Error");
	if (read(fd, &tmp, 1) != 0)	/* Perhaps it doesn't work. */
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
	char			*arr;
	int				i;
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
**
** We loop through an array of arguments in the table,
** loop through of types in that argument,
** and check if this argument can be here,
** we save this type of argument.
*/

char		*pseudo_codage(char opcode)
{
	char			*arr;
	unsigned char	i;
	unsigned char	j;

	i = 0;
	(!(arr = (char *)ft_memalloc(4))) ? ft_error("Error") : 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (ARG(opcode, i, j))
			{
				arr[i] = j + 1;
				break ;
			}
			j++;
		}
		i++;
	}
	return (arr);
}

void		check_arguments(char opcode, char *types, t_bot *bot, unsigned int *i)
{
	unsigned char	count;

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

void		check_command(t_bot *new, unsigned int *i)
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

/*
** This function checks executable of a bot.
**
** Specifically this function checks whether i points on opcode or not.
** i - it is a counter for the whole executable 
** which will skip in function check_command
** command + codage + arguments.
*/

void		check_executable(t_bot *bot)
{
	unsigned int	i;

	i = 0;
	while (i < bot->size)
	{
		if (bot->exec[i] > 0 && bot->exec[i] <= MAX_TABLE)
			check_command(bot, &i);
		else
			ft_error("Error");
	}
}

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

/*
** This function gets a value of some sequence of bytes
** size of which specified in arg_size and returns reversed value.
*/

unsigned int	get_arg(unsigned int i, char arg_size)
{
	unsigned int	arg;
	unsigned char	str[4];
	unsigned char	j;

	j = 0;
	arg = 0;
	ft_bzero(str, 4);
	while (j < arg_size)
	{
		((i + j) >= MEM_SIZE) ? (i = 0) : 0;
		str[j] = g_map[i + j];
		j++;
	}
	((unsigned char *)&arg)[0] = ((unsigned char *)&str)[0];
	((unsigned char *)&arg)[1] = ((unsigned char *)&str)[1];
	((unsigned char *)&arg)[2] = ((unsigned char *)&str)[2];
	((unsigned char *)&arg)[3] = ((unsigned char *)&str)[3];
	return (reverse_bytes(arg, arg_size));
}

void		bot_parsing(int fd, t_bot *new)
{
	check_magic_header(fd);
	get_name(fd, new);
	get_size(fd, new);
	get_comment(fd, new);
	get_executable(fd, new);
	check_executable(new);
}

void		get_bot(t_vm *vm, unsigned int id, char *filename)
{
	int			fd;
	t_bot		*new;

	vm->count_players++;	
	if (vm->count_players > 4)
		ft_error("Error");
	new = push_new_bot(&vm->bot, id);
	if ((fd = open(filename, O_RDONLY)) < 0 || read(fd, 0, 0) == -1)
		ft_error("Error");
	bot_parsing(fd, new);
	close(fd);
}

void		get_number_bot(t_vm *vm, char **args, int count, int *i)
{
	unsigned int	id;

	(*i)++;
	if (*i < count && ft_is_uint(args[*i]))
	{
		id = ft_atoi(args[*i]);
		(id > 4 || id == 0) ? ft_error("Error") : (*i)++;
		(*i < count) ? get_bot(vm, id * -1, args[*i]) : usage();
	}
	else
		usage();
}

char	is_uchar(char *s)
{
	int				num;
	unsigned char	i;

	num = 0;
	i = 0;
	while (ft_is_digit(s[i]) && i < 3)
		num = num * 10 + s[i++] - '0';
	return ((i == 0 || s[i] != '\0' || num > 255) ? 0 : 1);
}

char	is_ushort(char *s)
{
	int				num;
	unsigned char	i;

	num = 0;
	i = 0;
	while (ft_is_digit(s[i]) && i < 6)
		num = num * 10 + s[i++] - '0';
	return ((i == 0 || s[i] != '\0' || num > 65535) ? 0 : 1);
}

char		*get_ip(char *s)
{
	char			**octets;
	unsigned char	i;
	unsigned char	n_commas;

	(!(octets = ft_strsplit(s, '.'))) ? ft_error("Error") : 0;
	i = 0;
	while (octets[i])
		(!is_uchar(octets[i])) ? ft_error("Error") : ft_strdel(octets[i++]);
	(i != 4) ? ft_error("Error") : free(octets);
	i = 0;
	n_commas = 0;
	while (s[i])
	{
		(s[i] == '.') ? (n_commas++) : 0;
		(n_commas > 3) ? ft_error("Error") : 0;
		i++;
	}
	return (s);
}

unsigned short		get_port(char *s)
{
	if (!is_ushort(s) || ft_atoi(s) == 0)
		ft_error("Error");
	return ((unsigned short)ft_atoi(s));
}

void		get_server_ip_port(t_vm *vm, char *args[], int argv, int &i)
{
	vm->flag_server = 1;
	(*i)++;
	if (*i >= argv)
		ft_error("Error");
	else
		vm->ip = get_ip(args[*i]);
	(*i)++;
	if (*i >= argv)
		ft_error("Error");
	else
		vm->port = get_port(args[*i]);
}

/*
** We go through an array of args and check whether
** argument is -dump, -n, -s (server), -c (client) or simply .cor file,
** and call corresponding functions.
*/

void		get_args(t_vm *vm, int count, char **args)
{
	int				i;
	unsigned int	id;

	id = 0;
	i = 1;
	while (i < count)
	{
		if (ft_strequ(args[i], "-dump"))
			get_dump(vm, args, count, &i);
		else if (ft_strequ(args[i], "-n"))
			get_number_bot(vm, args, count, &i);
		else if (ft_strequ(args[i], "-v"))
			vm->flag_visual = 1;
		else if (ft_strequ(args[i], "-s"))
			get_server_ip_port(vm, args, count, &i);
		else if (ft_strequ(args[i], "-c"))
			vm->flag_client = 1;
		else
		{
			id--;
			get_bot(vm, id, args[i]);
		}
		i++;
	}
	(vm->count_players == 0) ? usage() : 0;
}

t_process	*push_new_process(t_process **head, unsigned int *process_count, t_bot *parent, unsigned int position)
{
	t_process	*new;

	new = (t_process *)malloc(sizeof(t_process));
	(!new) ? ft_error("Error") : 0;
	ft_bzero(new->registries, REG_NUMBER + 1);
	new->registries[1] = parent->id;
	new->parent = parent;
	new->position = position;
	new->carry = 0;
	new->live = 0;
	new->opcode = 0;
	new->codage = 0;
	new->cycles_to_perform = 0;
	new->next = NULL;
	if (*head)
		new->next = *head;
	*head = new;
	(*process_count)++;
	return (new);
}

void		fill_map(t_vm *vm, char count_players)
{
	t_bot			*bot;
	unsigned int	i;
	unsigned int	total;

	total = 0;
	bot = vm->bot;
	while (bot)
	{
		i = 0;
		push_new_process(&vm->process, &vm->process_count, bot, total + i);
		while (i < bot->size)
		{
			g_map[total + i] = bot->exec[i];
			i++;
		}
		total += MEM_SIZE / count_players;
		bot = bot->next;
	}
}

int			main(int ac, char **av)
{
	t_vm		*vm;

	if (ac > 1)
	{
		vm = init_vm();
		get_args(vm, ac, av);
		fill_map(vm, vm->count_players);
		// if (vm->flag_visual)
		// 	visualize(vm);
		// else
		// 	while (!vm->winner)
		// 		;// step(vm);
	}
	else
		usage();
	return (0);
}
