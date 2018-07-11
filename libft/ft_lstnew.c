/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 19:43:45 by opavliuk          #+#    #+#             */
/*   Updated: 2018/03/28 21:17:14 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (list)
	{
		list->content = NULL;
		list->content_size = 0;
		list->next = NULL;
		if (content == NULL)
			return (list);
		list->content = malloc(content_size);
		if (list->content)
		{
			ft_memcpy(list->content, content, content_size);
			list->content_size = content_size;
			list->next = NULL;
		}
		else
		{
			free(list);
			list = NULL;
		}
	}
	return (list);
}
