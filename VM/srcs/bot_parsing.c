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

static void			get_name(int fd, t_bot *new)
{
	unsigned char	buf[4];
	unsigned char	i;

	if (read(fd, &new->name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
		ft_error("Error");
	if (read(fd, &buf, 4) != 4)
		ft_error("Error");
	i = 0;
	while (i < 4)
		(buf[i] != 0) ? ft_error("Error") : i++;
}

static void			get_size(int fd, t_bot *new)
{
	if (read(fd, &new->size, 4) != 4)
		ft_error("Error");
	new->size = reverse_bytes(new->size, 4);
	if (new->size > CHAMP_MAX_SIZE)
		ft_error("Error");
}

static void			get_comment(int fd, t_bot *new)
{
	unsigned char	buf[4];
	unsigned char	i;

	if (read(fd, &new->comment, COMMENT_LENGTH) != COMMENT_LENGTH)
		ft_error("Error");
	if (read(fd, &buf, 4) != 4)
		ft_error("Error");
	i = 0;
	while (i < 4)
		(buf[i] != 0) ? ft_error("Error") : i++;
}

static void			get_executable(int fd, t_bot *new)
{
	unsigned char	tmp[1];

	new->exec = (unsigned char *)malloc(new->size + 1);
	if (!new->exec)
		ft_error("Error");
	if (read(fd, new->exec, new->size) != new->size)
		ft_error("Error");
	if (read(fd, &tmp, 1) != 0)
		ft_error("Error");
}

void				bot_parsing(int fd, t_bot *new)
{
	check_magic_header(fd);
	get_name(fd, new);
	get_size(fd, new);
	get_comment(fd, new);
	get_executable(fd, new);
	check_executable(new);
}
