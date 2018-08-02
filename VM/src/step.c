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

void	delta_cycle()
{
	g_vm->cycle_to_die -= CYCLE_DELTA;
	g_vm->last_change_cycle_to_die = 0;
}

int		reset_cur_period()
{
	t_bot		*cur_bot;
	int			max;

	max = 0;
	cur_bot = g_vm->bot;
	while(cur_bot)
	{
		max = (cur_bot->lives_cur_period > max) ? cur_bot->lives_cur_period : 0;
		cur_bot->lives_last_period = cur_bot->lives_cur_period;
		cur_bot->lives_cur_period = 0;
		cur_bot = cur_bot->next;
	}
	return (max > 21 ? 1 : 0);
}

void	time_to_die()
{
	t_process	*cur_p;
	t_process	*prev;

	prev = 0;
	cur_p = g_vm->process; 
	ft_printf("|||die %d|||\n", g_vm->cycle_to_die);
	while(cur_p)
	{																	// !!!!!!!!!!!!!!!!!!!!
		if (!(cur_p->live))
		{
			prev ? prev->next = cur_p->next : 0;
			!prev ? g_vm->process = cur_p->next : 0;
			free(cur_p);
			g_vm->process_count--;
			cur_p = prev ? prev->next : g_vm->process;
		}
		else
		{
			cur_p->live = 0;
			prev = cur_p;
			cur_p = cur_p->next;
		}

	}
}

void	do_proceses()
{
	t_process *curent;

	curent = g_vm->process;
	while(curent)
	{
		if (!curent->opcode)
		{
			if (!g_map[curent->position] || g_map[curent->position] > 16)
				curent->position = ((curent->position) + 1) % MEM_SIZE;
			else
			{
																				// ft_printf("%02x  %d\n", g_map[curent->position], curent->position);
				curent->opcode = g_map[curent->position];
				curent->cycles_to_perform = PREFORM(curent->opcode) - 1;
			}
		}
		else if (curent->cycles_to_perform > 0)
			curent->cycles_to_perform--;
		else if (!curent->cycles_to_perform)
		{
			g_func[curent->opcode - 1](curent);									// ? call function
			curent->opcode = 0;
		}
		curent = curent->next;
	}
}

t_bot		*winner_bot()
{
	t_bot			*cur_bot;
	t_bot			*winner_bot;
	unsigned int	min;

	min = UINT32_MAX;
	cur_bot = g_vm->bot;
	winner_bot = 0;
	while(cur_bot)
	{
		if (cur_bot->last_live < min)
		{
			min =  cur_bot->last_live;
			winner_bot = cur_bot;
		}
		cur_bot = cur_bot->next;
	}
	return (winner_bot);
}

int		step()
{
	do_proceses();
	if (g_vm->cur_cycle && !(g_vm->cur_cycle % g_vm->cycle_to_die))
	{
		// ft_printf("%s:%d value", curent->parent->name, curent->position);
		time_to_die();
		reset_cur_period() ? delta_cycle() : 0;								// ? cut cycle_to_die when "live" greater than 21
		g_vm->last_change_cycle_to_die > 10 ? delta_cycle(): 0;					// ? cut cycle_to_die when it had no changes more then 10 steps
		g_vm->last_change_cycle_to_die++;
	}
	g_vm->cur_cycle++;
	(!g_vm->process || g_vm->cycle_to_die < 1) ? g_vm->winner = winner_bot() : 0;
	return (0);
}