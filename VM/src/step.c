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
	if (CYCLE_DELTA < g_vm->cycle_to_die)
		g_vm->cycle_to_die -= CYCLE_DELTA;
	else
		g_vm->cycle_to_die = 0;
	g_vm->last_change_cycle_to_die = 0;
}

int		reset_cur_period()
{
	t_bot		*cur_bot;
	unsigned	max;

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
	while(cur_p)
	{
		if (!(cur_p->live))
		{
			prev ? prev->next = cur_p->next : 0;
			!prev ? g_vm->process = cur_p->next : 0;
			(g_vm->flag_visual) ? (g_pixels[cur_p->position]->color =
				g_pixels[cur_p->position]->color % 10) : 1;
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
	t_process *process;
	static	int i = 0;
	int			j = 1;

	process = g_vm->process;
	ft_printf("HAHA do_process: cur_cycle %d | process_cout %d\n", g_vm->cur_cycle, g_vm->process_count);
	while(process)
	{
		if (!process->opcode)
		{
			ft_printf(" !opcode sart with process pos %u\n", process->position);
			if (!g_map[process->position] || g_map[process->position] > 16)
			{
				ft_printf("bag opcode sart\n");
				(g_vm->flag_visual) ? SET_PIXEL_COLOR : 1;
				process->position = ((process->position) + 1) % MEM_SIZE;
				(g_vm->flag_visual) ? TURN_ON_PROCESS : 1;
				ft_printf("bad opcode end\n");
			}
			else
			{
				ft_printf("good opcode start\n");
				process->opcode = g_map[process->position];
				process->cycles_to_perform = PREFORM(process->opcode) - 1;
				ft_printf("good opcode end\n");
			}
			ft_printf(" !opcode end\n");
		}
		else if (process->cycles_to_perform > 0)
			process->cycles_to_perform--;
		else if (!process->cycles_to_perform)
		{
			ft_printf("func call start\n");
			g_func[process->opcode - 1](process);			// ? call function
			process->opcode = 0;
			ft_printf("func call end\n");
		}
		// fprintf(g_f, "	do_process: in cycle ->%d<- process_position is ->%d<- num of call %d opcode %d COLOR ->%d<-\n", g_vm->cur_cycle, process->position, i, process->opcode, g_pixels[process->position]->color);
		ft_printf("do_process: cur_cycle %d | process_cout %d | cycle is checked %d\n", g_vm->cur_cycle, g_vm->process_count, j);
		process = process->next;
		j++;
	}
	ft_printf("DO_PROCESS CALLED %d times\n", i);
	i++;
}

t_bot	*winner_bot()
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

int		step(void)
{
	do_proceses();
	if (g_vm->cur_cycle && !(g_vm->cur_cycle % g_vm->cycle_to_die))
	{
		time_to_die();
		reset_cur_period() ? delta_cycle() : 0;								// ? cut cycle_to_die when "live" greater than 21
		g_vm->last_change_cycle_to_die > 10 ? delta_cycle(): 0;					// ? cut cycle_to_die when it had no changes more then 10 steps
		g_vm->last_change_cycle_to_die++;
	}
	g_vm->cur_cycle++;
	(!g_vm->process || !g_vm->cycle_to_die) ? g_vm->winner = winner_bot() : 0;
	return (0);
}