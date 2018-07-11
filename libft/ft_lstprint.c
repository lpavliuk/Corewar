/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 14:22:17 by opavliuk          #+#    #+#             */
/*   Updated: 2018/03/28 21:22:23 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list *list)
{
	size_t i;

	i = 0;
	if (list)
	{
		while (list)
		{
			ft_putstr(ft_itoa(i));
			ft_putchar(':');
			ft_putstr((char *)(list->content));
			ft_putchar('\n');
			list = list->next;
			i++;
		}
	}
}
