/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 10:56:29 by opavliuk          #+#    #+#             */
/*   Updated: 2018/03/28 20:54:38 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list *ping;

	if (lst && (*f))
	{
		ping = lst;
		while (ping)
		{
			f(ping);
			ping = ping->next;
		}
	}
}
