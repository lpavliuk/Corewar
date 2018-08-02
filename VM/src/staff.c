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

void				usage(void)
{
	ft_printf("USAGE\n");
	exit(0);
}

void				ft_error(char *s)
{
	ft_printf("%s\n", s);
	exit(0);
}

unsigned int		reverse_bytes(unsigned int data, char bytes)
{
	unsigned int	res;

	res = data;
	if (bytes == 4)
	{
		((unsigned char *)&res)[0] = ((unsigned char *)&data)[3];
		((unsigned char *)&res)[1] = ((unsigned char *)&data)[2];
		((unsigned char *)&res)[2] = ((unsigned char *)&data)[1];
		((unsigned char *)&res)[3] = ((unsigned char *)&data)[0];
	}
	else if (bytes == 2)
	{
		((unsigned char *)&res)[0] = ((unsigned char *)&data)[1];
		((unsigned char *)&res)[1] = ((unsigned char *)&data)[0];
	}
	return (res);
}

/*
** This function gets a value of some sequence of bytes
** size of which specified in arg_size and returns reversed value.
*/

unsigned int		get_arg(unsigned int i, char arg_size)
{
	unsigned int	arg;
	unsigned char	str[4];
	unsigned char	j;

	j = 0;
	arg = 0;
	ft_bzero(str, 4);
	while (j < arg_size)
	{
		((i + j) >= MEM_SIZE) ? (i = 0) : 0;
		str[j] = g_map[i + j];
		j++;
	}
	((unsigned char *)&arg)[0] = ((unsigned char *)&str)[0];
	((unsigned char *)&arg)[1] = ((unsigned char *)&str)[1];
	((unsigned char *)&arg)[2] = ((unsigned char *)&str)[2];
	((unsigned char *)&arg)[3] = ((unsigned char *)&str)[3];
	return (reverse_bytes(arg, arg_size));
}

t_process			*push_new_process(t_process **head, unsigned int
					*process_count, t_bot *parent, unsigned int position)
{
	t_process	*new;

	new = (t_process *)malloc(sizeof(t_process));
	(!new) ? ft_error("Error") : 0;
	ft_bzero(new->registries, REG_NUMBER + 1);
	new->registries[1] = parent->id;
	new->parent = parent;
	new->position = position;
	new->carry = 0;
	new->live = 0;
	new->opcode = 0;
	new->codage = 0;
	new->cycles_to_perform = 0;
	new->next = 0;
	if (*head)
		new->next = *head;
	*head = new;
	(*process_count)++;
	return (new);
}
