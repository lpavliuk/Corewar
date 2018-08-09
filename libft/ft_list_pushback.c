/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_pushback.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 15:54:06 by tkiselev          #+#    #+#             */
/*   Updated: 2018/07/13 15:54:09 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_list_pushback(t_list **head, char *line)
{
	t_list	*tmp;
	t_list	*new;

	tmp = *head;
	while (tmp)
	{
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return ;
	new->content = ft_strdup(line);
	new->content_size = ft_strlen(line);
	new->next = NULL;
	if (!*head)
		*head = new;
	else
		tmp->next = new;
}
