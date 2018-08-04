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

void	get_game(int socket_fd, fd_set read_fds)
{
	// struct timeval	timeout;

	// timeout.tv_sec = 1;
	// timeout.tv_usec = 0;
	while (select(socket_fd + 1, &read_fds, NULL, NULL, 0) > 0)
	{
		if (recv(socket_fd, &g_map, sizeof(g_map), 0) > 0)
			print_memory(g_map, sizeof(g_map));
	}
}
