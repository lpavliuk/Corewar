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

static void		get_dump(char **args, int count, int *i)
{
	(*i)++;
	if (*i < count && ft_is_uint(args[*i]))
	{
		g_vm->flag_dump = 1;
		g_vm->dump_cycles = ft_atoi(args[*i]);
	}
	else
		usage();
}

static void		get_bot(unsigned int id, char *filename)
{
	int			fd;
	t_bot		*new;

	g_vm->count_players++;	
	if (g_vm->count_players > 4)
		ft_error("Error");
	if ((fd = open(filename, O_RDONLY)) < 0 || read(fd, 0, 0) == -1)
		ft_error("Error");
	new = push_new_bot(&g_vm->bot, id);
	bot_parsing(fd, new);
	close(fd);
}

static void		get_number_bot(char **args, int count, int *i)
{
	unsigned int	id;

	(*i)++;
	if (*i < count && ft_is_uint(args[*i]))
	{
		id = ft_atoi(args[*i]);
		(id > 4 || id == 0) ? ft_error("Error") : (*i)++;
		(*i < count) ? get_bot(id * -1, args[*i]) : usage();
	}
	else
		usage();
}

/*
** We go through an array of args and check whether
** argument is -dump, -n, -s (server), -c (client) or simply .cor file,
** and call corresponding functions.
*/

char			is_flag(char *s)
{
	if (ft_strequ(s, "-dump"))
		return (1);
	else if (ft_strequ(s, "-n"))
		return (1);
	else if (ft_strequ(s, "-v"))
		return (1);
	else if (ft_strequ(s, "-s"))
		return (1);
	else if (ft_strequ(s, "-c"))
		return (1);
	return (0);
}

void			get_arg_through_flag(int count, char **args, int *i)
{
	if (ft_strequ(args[*i], "-dump"))
		get_dump(args, count, i);
	else if (ft_strequ(args[*i], "-n"))
		get_number_bot(args, count, i);
	else if (ft_strequ(args[*i], "-v"))
		g_vm->flag_visual = 1;
	else if (ft_strequ(args[*i], "-s"))
		get_info_server(args, count, i);
	else if (ft_strequ(args[*i], "-c"))
		get_info_client(args, count, i);
}

void			get_args(int count, char **args)
{
	int				i;
	unsigned int	id;

	id = 0;
	i = 0;
	while (++i < count)
	{
		if (is_flag(args[i]))
			get_arg_through_flag(count, args, &i); 
		else
		{
			id--;	/* Remake this shit cause it doesn't work correctly */
			get_bot(id, args[i]);
		}
	}
	(g_vm->count_players == 0) ? usage() : 0;
}
