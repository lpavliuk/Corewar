/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 11:13:20 by opavliuk          #+#    #+#             */
/*   Updated: 2018/03/28 20:53:57 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_lstdelete(t_list **alst)
{
	t_list *ping;

	ping = *alst;
	if (alst != NULL && *alst != NULL)
	{
		while (ping)
		{
			free(ping);
			ping = ping->next;
		}
		*alst = NULL;
	}
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *ping;
	t_list *tmp;

	if (lst && (*f))
	{
		if (!(ping = f(lst)))
			return (NULL);
		tmp = ping;
		lst = lst->next;
		while (lst)
		{
			if (!(ping->next = f(lst)))
			{
				ft_lstdelete(&tmp);
				return (NULL);
			}
			ping = ping->next;
			lst = lst->next;
		}
		return (tmp);
	}
	return (NULL);
}
