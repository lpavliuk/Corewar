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

void		dispatcher_routes(t_vm *vm)
{
	if (vm->flag_client || vm->flag_server)
	{
		if (vm->flag_client && vm->flag_server)
			ft_error("Error");
		// else if ((vm->flag_client))
		// 	client(vm);
		// else
		// 	server(vm);	/* Here we need to fill a map. */
	}
	else
	{
		fill_map(vm, vm->count_players);
		if (vm->flag_visual)
			visualize(vm);
		else
			while (!vm->winner)
				;// step(vm);
	}
}


/* >>>>> SORT BOT LIST <<<<< */

static void		bot_swap(t_bot **head, t_bot *prev, t_bot **cur, t_bot **next)
{
	t_bot		*tmp;

	(*cur)->next = (*next)->next;
	(*next)->next = *cur;
	if (prev)
		prev->next = *next;
	else
		*head = *next;
	tmp = *next;
	*next = *cur;
	*cur = tmp;
}

void			sort_bot_list(t_bot **head)
{
	t_bot		*tmp;
	t_bot		*prev;
	t_bot		*cur;
	t_bot		*next;

	tmp = *head;
	while (tmp && tmp->next)
	{
		prev = NULL;
		cur = *head;
		next = cur->next;
		while (next)
		{
			if (cur->id < next->id)
				bot_swap(head, prev, &cur, &next);
			prev = cur;
			cur = next;
			next = next->next;
		}
		tmp = tmp->next;
	}
}

// int			main(int ac, char **av)
// {
// 	t_vm		*vm;

// 	if (ac > 1)
// 	{
// 		vm = init_vm();
// 		get_args(vm, ac, av);
// 		sort_bot_list(&vm->bot);
// 		dispatcher_routes(vm);
// 	}
// 	else
// 		usage();
// 	return (0);
// }
