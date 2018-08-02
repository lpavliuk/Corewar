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

static void		get_dump(t_vm *vm, char **args, int count, int *i)
{
	(*i)++;
	if (*i < count && ft_is_uint(args[*i]))
	{
		vm->flag_dump = 1;
		vm->dump_cycles = ft_atoi(args[*i]);
	}
	else
		usage();
}

static void		get_bot(t_vm *vm, unsigned int id, char *filename)
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

static void		get_number_bot(t_vm *vm, char **args, int count, int *i)
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

/*
** We go through an array of args and check whether
** argument is -dump, -n, -s (server), -c (client) or simply .cor file,
** and call corresponding functions.
*/

void			get_args(t_vm *vm, int count, char **args)
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
			get_server_info(vm, args, count, &i);
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
