/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 13:21:59 by tkuhar            #+#    #+#             */
/*   Updated: 2018/08/01 13:21:59 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

void		print_header(t_vm *vm)
{
	t_bot			*cur_bot;
	char			i;

	ft_printf("Introducing contestants...\n");
	i = 1;
	while(i < vm->count_players)
	{
		cur_bot = vm->bot;
		while(cur_bot && cur_bot->id != i)
			cur_bot = cur_bot->next;
		ft_printf("* Player %u, weighing %u bytes, \"%s\" (\"%s\") !\n",
			i, cur_bot->size, cur_bot->name, cur_bot->comment);
		i++;
	}
}

void		dump_print()
{
	int		i;

	i = -1;
	while(++i < MEM_SIZE)
	{
		if (!(i % 64))
			ft_printf("\n");
		if (!(i % 64))
			ft_printf("0x%6x :", i);
		ft_printf(" %c");
	}
	ft_printf("\n");
}

void		print_winer(t_vm *vm)
{
	ft_printf("Player %u (%s) won\n", vm->winner->id , vm->winner->name);
}