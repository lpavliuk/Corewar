/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 13:45:19 by tkiselev          #+#    #+#             */
/*   Updated: 2018/07/11 13:45:23 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			create_socket(void)
{
	int		socket_fd;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	(socket_fd < 0) ? ft_error(ERR_306) : 0;
	return (socket_fd);
}

void		foreach_sockets(t_server *server, unsigned char *str, int bytes)
{
	int		i;
	int		sd;

	i = 0;
	while (i < server->n_client_sockets)
	{
		sd = server->client_sockets[i];
		if (sd > 0)
			write(sd, str, bytes);
		i++;
	}
}

static void	ft_error_select(char *s)
{
	delwin(g_vm->win_link->window);
	endwin();
	ft_error(s);
	exit(0);
}

void		get_data_select(int socket_fd, fd_set read_fds, void *dest, int len)
{
	if (select(socket_fd + 1, &read_fds, NULL, NULL, NULL) > 0)
	{
		if (recv(socket_fd, dest, len, 0) <= 0)
			ft_error_select(ERR_301);
	}
	else
		ft_error_select(ERR_301);
}