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

#include "../corewar.h"


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
// static void					get_info_server(t_vm *vm, char *args[], int argv, int *i)
// {
// 	vm->flag_server = 1;
// 	(*i)++;
// 	if (*i >= argv)
// 		ft_error("Error");
// 	else
// 		vm->ip = args[*i];
// }

// static void					get_info_client(t_vm *vm, char *args[], int argv, int *i)
// {
// 	vm->flag_client = 1;
// 	(*i)++;
// 	if (*i >= argv)
// 		ft_error("Error");
// 	else
// 		vm->ip = args[*i];
// }

/*-------------------------------------------------------------------------------------*/




void			get_args(int count, char **args)
{
	int				i;

	i = 0;
	while (++i < count)
		parse_argument(count, args, &i);
	(g_vm->count_players == 0 && !g_vm->flag_server) ? usage() : 0;
}



// void			get_args(t_vm *vm, int count, char **args)
// {
// 	int				i;

// 	i = 1;
// 	while (i < count)
// 	{
// 		if (ft_strequ(args[i], "-s"))
// 			get_info_server(vm, args, count, &i);
// 		else if (ft_strequ(args[i], "-c"))
// 			get_info_client(vm, args, count, &i);
// 		i++;
// 	}
// }

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
