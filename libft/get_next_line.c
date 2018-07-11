/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 17:10:05 by opavliuk          #+#    #+#             */
/*   Updated: 2018/04/16 22:50:50 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*check_list(t_list **gnl, const int fd)
{
	t_list *tmp;

	if ((*gnl)->content == NULL)
		(*gnl)->content_size = -1;
	tmp = *gnl;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew(NULL, 0);
	tmp->content = ft_strnew(BUFF_SIZE);
	tmp->content_size = fd;
	ft_lstadd(gnl, tmp);
	return (tmp);
}

static int		check_line(t_list *elem, char **line)
{
	char *n;

	if ((n = ft_strchr(elem->content, '\n')) != NULL)
	{
		ft_memset(n, '\0', 1);
		(*line) = ft_strdup(elem->content);
		ft_strncpy(elem->content, &n[1], BUFF_SIZE + 1);
		return (1);
	}
	(*line) = ft_strdup(elem->content);
	ft_strclr(elem->content);
	return (0);
}

static void		check_content(t_list *elem, char **line)
{
	char *n;
	char *mod;

	n = ft_strchr(elem->content, '\n');
	if (n != NULL)
		ft_memset(n, '\0', 1);
	mod = *line;
	(*line) = ft_strjoin((*line), elem->content);
	free(mod);
	if (n)
		ft_strncpy(elem->content, &n[1], BUFF_SIZE + 1);
	else
		ft_strclr(elem->content);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*gnl;
	t_list			*elem;
	int				k;

	if (fd < 0 || !line)
		return (-1);
	*line = NULL;
	k = 0;
	if (!gnl)
		gnl = ft_lstnew(NULL, 0);
	elem = check_list(&gnl, fd);
	if (read(fd, elem->content, 0) < 0)
		return (-1);
	if (check_line(elem, line))
		return (1);
	while ((k = read(elem->content_size, elem->content, BUFF_SIZE)) > 0)
	{
		if (ft_strchr(elem->content, '\n') != NULL)
			break ;
		check_content(elem, line);
	}
	check_content(elem, line);
	if (k == 0 && ft_strlen(*line) == 0)
		return (0);
	return ((k == -1) ? -1 : 1);
}
