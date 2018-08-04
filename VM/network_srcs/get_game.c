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

// static void		ft_prepare_pixel_map(void)
// {
// 	unsigned short	i;

// 	i = 0;
// 	while (i < MEM_SIZE)
// 	{
// 		g_pixels[i] = (t_pixel *)malloc(sizeof(t_pixel));
// 		(!g_pixels[i]) ? ft_error("Error") : 0;
// 		i++;
// 	}
// }

// void	get_game(int socket_fd, fd_set read_fds)
// {
// 	char flag_map;
// 	char flag_pixel;
// 	int n;
// 	// struct timeval	timeout;

// 	// timeout.tv_sec = 1;
// 	// timeout.tv_usec = 0;
// 	flag_map = 0;
// 	flag_pixel = 0;
// 	n = 0;
// 	g_pixels = (t_pixel **)malloc(sizeof(t_pixel *) * MEM_SIZE);
// 	(!g_pixels) ? ft_error("Error") : ft_prepare_pixel_map();
// 	while (select(socket_fd + 1, &read_fds, NULL, NULL, NULL) > 0)
// 	{
// 		if (!flag_map && !flag_pixel && recv(socket_fd, &g_map, MEM_SIZE, 0) > 0)
// 		{
// 			print_memory(g_map, MEM_SIZE);
// 			flag_map = 1;
// 		}
// 		else if (!flag_pixel && flag_map &&
// 			recv(socket_fd, g_pixels[n], 2, 0) > 0)
// 		{
// 			n++;
// 			if (n == MEM_SIZE)
// 				flag_pixel = 1;
// 		}
// 	}
// }


void	get_pixel_map(int socket_fd)
{
	int i;

	i = 0;
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
	ft_prepare_pixel_map();
	while (select(socket_fd + 1, &read_fds, NULL, NULL, NULL) > 0)
	{
		recv(socket_fd, &g_map, MEM_SIZE, 0);
		get_pixel_map(socket_fd);
	}
}
