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

#include "../corewar.h"

int			create_socket(void)
{
	int		socket_fd;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	(socket_fd < 0) ? ft_error("Error: create_socket()") : 0;
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
			send(sd, str, bytes, 0);
		i++;
	}
}
