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

char				get_arg_size(char opcode, char type)
{
	if (type == REG_CODE)
		return (T_REG_SIZE);
	else if (type == IND_CODE)
		return (T_IND_SIZE);
	else
	{
		if (LABEL_SIZE(opcode) == 4)
			return (4);
		else
			return (T_DIR_SIZE);
	}
}

/*
** Here I make bit-by-bit operation & for the last two bits in codage,
** as you may have guessed, with the number of 192 (128 + 64),
** and check whether these bits are on / off.
** After that I make a bitwise shift left on two bits.
*/

char				*decipher_codage(unsigned char codage)
{
	char			*arr;
	int				i;
	unsigned char	tmp;

	i = 0;
	(!(arr = (char *)ft_memalloc(4))) ? ft_error("Error") : 0;
	while (codage)
	{
		(i == 3) ? ft_error("Error") : 0;
		tmp = codage & 192;
		(tmp == 192) ? (arr[i] = IND_CODE) : 0;
		(tmp == 128) ? (arr[i] = DIR_CODE) : 0;
		(tmp == 64) ? (arr[i] = REG_CODE) : 0;
		(tmp == 0) ? ft_error("Error") : 0;
		codage <<= 2;
		i++;
	}
	return (arr);
}

/*
** This is the function that makes an array of types
** which must be presented after particular opcode,
** however such a function doesn't have at it's disposal
** such thing as codage.
**
** We loop through an array of arguments in the table,
** loop through of types in that argument,
** and check if this argument can be here,
** we save this type of argument.
*/

char				*pseudo_codage(char opcode)
{
	char			*arr;
	unsigned char	i;
	unsigned char	j;

	i = 0;
	(!(arr = (char *)ft_memalloc(4))) ? ft_error("Error") : 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (ARG(opcode, i, j))
			{
				arr[i] = j + 1;
				break ;
			}
			j++;
		}
		i++;
	}
	return (arr);
}

static t_bot		*bot_init(unsigned int id, unsigned char player_counter)
{
	t_bot			*new;

	new = (t_bot *)malloc(sizeof(t_bot));
	(!new) ? ft_error("Error") : 0;
	new->player_counter = player_counter;
	ft_bzero(new->name, PROG_NAME_LENGTH + 1);
	ft_bzero(new->comment, COMMENT_LENGTH + 1);
	new->exec = NULL;
	new->id = id;
	new->size = 0;
	new->lives_cur_period = 0;
	new->lives_last_period = 0;
	new->last_live = 0;
	new->next = NULL;
	return (new);
}

t_bot				*push_new_bot(t_bot **head, unsigned int id)
{
	unsigned char	player_counter;
	t_bot			*tmp;
	t_bot			*new;

	player_counter = 1;
	tmp = *head;
	while (tmp)
	{
		player_counter++;
		if (tmp->id == id)
			ft_error("Error");
		else if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	new = bot_init(id, player_counter);
	if (!*head)
		*head = new;
	else
		tmp->next = new;
	return (new);
}
