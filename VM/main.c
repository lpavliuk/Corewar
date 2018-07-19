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
	new->count_bots = 0;
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
	ft_bzero(new->name, PROG_NAME_LENGTH);
	ft_bzero(new->comment, COMMENT_LENGTH);
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

void		check_magic_header(int fd)
{
	unsigned int	header;
	unsigned char	*s;

	(read(fd, &header, 4) != 4) ? ft_error("Error") : 0;

	s = (unsigned char *)&header;

	printf("magic header = %d\n", s[0]);
	printf("magic header = %d\n", s[1]);
	printf("magic header = %d\n", s[2]);
	printf("magic header = %d\n", s[3]);
	printf("COREWAR_EXEC_MAGIC = %u\n", COREWAR_EXEC_MAGIC);
}

// void		get_name(int fd, t_bot *new)
// {

// }

// void		get_comment(int fd, t_bot *new)
// {

// }

// void		get_executable(int fd, t_bot *new)
// {

// }

void		bot_parsing(int fd, t_bot *new)
{
	check_magic_header(fd);
	// get_name(fd, new);
	// get_comment(fd, new);
	// get_executable(fd, new);
}

void		get_bot(t_vm *vm, unsigned int player, char *filename)
{
	int		fd;
	t_bot	*new;

	new = push_new_bot(&vm->bot, player);
	if ((fd = open(filename, O_RDONLY)) < 0)
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
		(*i)++;
		(*i < count) ? get_bot(vm, player, args[*i]) : usage();
	}
	else
		usage();
}

void		get_args(t_vm *vm, int count, char **args)
{
	int				i;
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
	t_vm	*vm;

	vm = init_vm();
	if (ac > 1)
	{
		get_args(vm, ac, av);
	}
	else
		usage();
	return (0);
}