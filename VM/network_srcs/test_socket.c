/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_socket.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 19:38:09 by opavliuk          #+#    #+#             */
/*   Updated: 2018/07/30 19:38:10 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		init_vm(void)
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
}

void			get_args(int count, char **args)
{
	int				i;

	i = 0;
	while (++i < count)
		parse_argument(count, args, &i);
	(g_vm->count_players == 0 && !g_vm->flag_server) ? usage() : 0;
}

/*-------------------------------------------------------------------------------------*/

int		main(int argc, char **argv)
{
	init_vm();
	get_args(argc, argv);

	if (g_vm->flag_client && g_vm->flag_server)
		ft_error("Error: main()");
	else if (g_vm->flag_client)
		client();
	else if (g_vm->flag_server)
		server();
	return (0);
}
