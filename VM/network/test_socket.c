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

static t_vm		*init_vm(void)
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

static void					get_info_server(t_vm *vm, char *args[], int argv, int *i)
{
	vm->flag_server = 1;
	(*i)++;
	if (*i >= argv)
		ft_error("Error");
	else
		vm->ip = args[*i];
}

static void					get_info_client(t_vm *vm, char *args[], int argv, int *i)
{
	vm->flag_client = 1;
	(*i)++;
	if (*i >= argv)
		ft_error("Error");
	else
		vm->ip = args[*i];
}

/*-------------------------------------------------------------------------------------*/





void			get_args(t_vm *vm, int count, char **args)
{
	int				i;

	i = 1;
	while (i < count)
	{
		if (ft_strequ(args[i], "-s"))
			get_info_server(vm, args, count, &i);
		else if (ft_strequ(args[i], "-c"))
			get_info_client(vm, args, count, &i);
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_vm	*vm;

	vm = init_vm();
	get_args(vm, argc, argv);

	if (vm->flag_client && vm->flag_server)
		ft_error("Error");
	else if (vm->flag_client)
		client(vm, argv[1]);
	else if (vm->flag_server)
		server(vm);
	return (0);
}
