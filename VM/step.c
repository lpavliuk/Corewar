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

int		step(t_vm *vm)
{
	t_process	*cur;
	cur = vm->process;
	while(cur)
	{
		if (!cur->opcode)
		{
			if (!g_map[cur->position])
				cur->position = (cur->position + 1) % MEM_SIZE;
			else
			{
				cur->opcode = CODAGE(g_map[cur->position] + 1) ?
					g_map[(cur->position + 1) % MEM_SIZE] : 0; //смотрим есть ли codage у функци если есть записиваем
				cur->cycles_to_perform = 
			}
		
		}
		if (cur->cycles_to_perform > 0)
			cur->cycles_to_perform--;
		else
			;// call function


	
		cur = cur->next;
	}
	// cut cycles to die 
	vm->cur_cycle++;
}