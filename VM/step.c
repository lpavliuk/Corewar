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


int		



int		step(t_vm *vm)
{
	t_process	*cur;
	int			i;

	cur = vm->process;
	while(cur)
	{
		if (!cur->opcode)
		{
			if (!g_map[cur->position] || g_map[cur->position] > 16)
			{
				cur->position = (cur->position + 1) % MEM_SIZE;
				if (vm->flag_visual)
						;// risuem cveta
			}
			else
			{
				cur->opcode = g_map[cur->position];
				cur->cycles_to_perform = CYCLES_TO_PERFORM(cur->opcode);
			}
		}
		else if (cur->cycles_to_perform > 0)
			cur->cycles_to_perform--;
		else
		{
			if ((i = 0/*chekfunc*/) == -1)
					;// call function
				cur->position + i; // move karetka
			if (vm->flag_visual)
				;// risuem cveta
		}
		cur = cur->next;
	}
	//kill proceses
	// cut cycles to die 
	vm->cur_cycle++;
}