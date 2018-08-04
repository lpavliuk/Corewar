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

void	get_pixel_map(int socket_fd)
{
	int i;

	i = 0;
	ft_prepare_pixel_map();
	while (i < MEM_SIZE)
	{
		recv(socket_fd, &g_pixels[i], 2, 0);
		ft_printf("counter = %d, color = %d\n", g_pixels[i]->counter, g_pixels[i]->color);
		i++;
	}
}

void	get_game(int socket_fd, fd_set read_fds)
{
	// struct timeval	timeout;

	// timeout.tv_sec = 1;
	// timeout.tv_usec = 0;
	while (select(socket_fd + 1, &read_fds, NULL, NULL, NULL) > 0)
	{
		recv(socket_fd, &g_map, MEM_SIZE, 0);
		get_pixel_map(socket_fd);
	}
}
