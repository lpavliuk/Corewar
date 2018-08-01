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
	new->dump_cycles = 0;
	new->cur_cycle = 0;
	new->process_count = 0;
	new->port = 0;
	new->ip = NULL;
	new->winner = NULL;
	new->process = NULL;
	new->bot = NULL;
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

// void		dispatcher_routes(t_vm *vm)
// {
	// if (vm->flag_client && vm->flag_server)
	// 	ft_error("Error");
	// else if (vm->flag_client)
	// 	client();
	// else if (vm->flag_server)
	// 	server();
	// else if (vm->flag_visual)
	// 	visualize();
	// else
	// 	while (!vm->winner)
	// 		step(vm);
// }

int			main(int ac, char **av)
{
	t_vm		*vm;

	if (ac > 1)
	{
		vm = init_vm();
		get_args(vm, ac, av);
		fill_map(vm, vm->count_players);
		// dispatcher_routes(vm);
		if (vm->flag_visual)
			visualize(vm);
		else
		{
			print_header(vm);
			while (!vm->winner)
			{
				step(vm);
				if (vm->flag_dump && vm->cur_cycle == vm->dump_cycles)
				{
					dump_print();
					break;
				}
			}
			vm->flag_dump ? 0 : print_winer(vm);
		}
	}
	else
		usage();
	return (0);
}
