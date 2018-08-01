/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 14:05:59 by tkuhar            #+#    #+#             */
/*   Updated: 2018/07/30 17:45:55 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

void	delta_cycle(t_vm *vm)
{
	vm->cycle_to_die -= CYCLE_DELTA;
	vm->last_change_cycle_to_die = 0;
}

int		reset_cur_period(t_vm *vm)
{
	t_bot		*cur_bot;
	int			max;

	max = 0;
	cur_bot = vm->bot;
	while(cur_bot)
	{
		max = (cur_bot->lives_cur_period > max) ? cur_bot->lives_cur_period : 0;
		cur_bot->lives_last_period = cur_bot->lives_cur_period;
		cur_bot->lives_cur_period = 0;
		cur_bot = cur_bot->next;
	}
	return (max > 21 ? 1 : 0);
}

void	time_to_die(t_vm *vm)
{
	t_process	*cur_p;
	t_process	*prev;

	prev = 0;
	cur_p = vm->process; 
	while(cur_p)
		if (!cur_p->live)
		{
			prev ? prev->next = cur_p->next : 0;
			!prev ? vm->process = cur_p->next : 0;
			free(cur_p);
			vm->process--;
			cur_p = prev ? prev->next : vm->process;
		}
		else
		{
			cur_p->live = 0;
			prev = cur_p;
			cur_p = cur_p->next;
		}
}

void	do_proceses(t_process *curent)
{
	while(curent)
	{
		if (!curent->opcode)
		{
			if (!g_map[curent->position] && g_map[curent->position] > 16)
				curent->position = (curent->position + 1) % MEM_SIZE;
			else
			{
				curent->opcode = g_map[curent->position];
				curent->cycles_to_perform = PREFORM(curent->position) - 1;
			}
		}
		else if (curent->cycles_to_perform > 0)
			curent->cycles_to_perform--;
		else if (!curent->cycles_to_perform)
		{
			;
			// func[curent->opcode - 1](curent, vm);									// ? call function
			curent->opcode = 0;
		}
		curent = curent->next;
	}
}

t_bot		*winner_bot(t_vm *vm)
{
	t_bot			*cur_bot;
	t_bot			*winner_bot;
	unsigned int	min;

	min = UINT32_MAX;
	cur_bot = vm->bot;
	winner_bot = 0;
	while(cur_bot)
	{
		if (cur_bot->last_live < min)
		{
			min =  cur_bot->last_live;
			winner_bot = cur_bot;
		}
	}
	return (winner_bot);
}

int		step(t_vm *vm)
{
	do_proceses(vm->process);
	if (!vm->cur_cycle && !(vm->cur_cycle % vm->cycle_to_die))
	{
		time_to_die(vm);
		reset_cur_period(vm) ? delta_cycle(vm) : 0;								// ? cut cycle_to_die when "live" greater than 21
		vm->last_change_cycle_to_die > 10 ? delta_cycle(vm): 0;					// ? cut cycle_to_die when it had no changes more then 10 steps
		vm->last_change_cycle_to_die++;
	}
	if (vm->cycle_to_die < 1 || !vm->process)
		vm->winner = winner_bot(vm);
	vm->cur_cycle++;
	return (0);
}