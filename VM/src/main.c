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

void		init_vm(void)
{
	if (!(g_vm = (t_vm *)malloc(sizeof(t_vm))))
		exit(0);
	ft_bzero(g_map, MEM_SIZE);
	g_vm->count_players = 0;
	g_vm->flag_visual = 0;
	g_vm->flag_dump = 0;
	g_vm->flag_server = 0;
	g_vm->flag_client = 0;
	g_vm->cycle_to_die = CYCLE_TO_DIE;
	g_vm->dump_cycles = 0;
	g_vm->cur_cycle = 0;
	g_vm->process_count = 0;
	g_vm->port = 0;
	g_vm->ip = NULL;
	g_vm->winner = NULL;
	g_vm->process = NULL;
	g_vm->bot = NULL;
	g_vm->last_change_cycle_to_die = 0;
}

void		fill_map(void)
{
	t_bot			*bot;
	unsigned int	i;
	unsigned int	total;

	total = 0;
	bot = g_vm->bot;
	while (bot)
	{
		i = 0;
		push_new_process(&g_vm->process, &g_vm->process_count, bot, total + i);
		while (i < bot->size)
		{
			g_map[total + i] = bot->exec[i];
			i++;
		}
		total += MEM_SIZE / g_vm->count_players;
		bot = bot->next;
	}
}

void		dispatcher_routes(void)
{
	if (g_vm->flag_client || g_vm->flag_server)
	{
		if (g_vm->flag_client && g_vm->flag_server)
			ft_error("Error: dispatcher_routes()");
		// else if ((g_vm->flag_client))
		// 	client();
		// else
		// 	server();	/* Here we need to fill a map. */
	}
	else
	{
		fill_map();
		if (g_vm->flag_visual)
			visualize(g_vm);
		else
			text_out();
	}
}

/*
** We go through an array of args and check whether
** argument is -dump, -n, -s (server), -c (client) or simply .cor file,
** and call corresponding functions.
*/

void			get_args(int count, char **args)
{
	int				i;

	i = 0;
	while (++i < count)
		parse_argument(count, args, &i);
	(g_vm->count_players == 0) ? usage() : 0;
}

int			main(int ac, char **av)
{
	if (ac > 1)
	{
		g_f = fopen("tmp2", "w");
		init_vm();
		get_args(ac, av);
		sort_bot_list(&g_vm->bot, g_vm->count_players);
		dispatcher_routes();
		fclose(g_f);
	}
	else
		usage();
	return (0);
}
