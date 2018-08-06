/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 14:27:00 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/04 14:27:01 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		send_bots_to_client(int socket_fd)
{
	t_bot	*bot;

	send(socket_fd, &g_vm->count_players, 1, 0);
	bot = g_vm->bot;
	while (bot)
	{
		send(socket_fd, bot->name, PROG_NAME_LENGTH, 0);
		send(socket_fd, bot->comment, COMMENT_LENGTH, 0);
		bot = bot->next;
	}
}

// static void		send_pixel_map_to_client(int socket_fd)
// {
// 	int	i;

// 	i = 0;
// 	while (i < MEM_SIZE)
// 		send(socket_fd, g_pixels[i++], 2, 0);
// }

// static void		send_other_data_to_client(int socket_fd)
// {
// 	t_bot	*bot;

// 	 VM data 
// 	send(socket_fd, &g_vm->cycle_to_die, 4, 0);
// 	send(socket_fd, &g_vm->cur_cycle, 4, 0);
// 	send(socket_fd, &g_vm->process_count, 4, 0);
// 	/* Bots' data */
// 	bot = g_vm->bot;
// 	while (bot)
// 	{
// 		send(socket_fd, &bot->lives_cur_period, 4, 0);
// 		send(socket_fd, &bot->lives_last_period, 4, 0);
// 		send(socket_fd, &bot->last_live, 4, 0);
// 		bot = bot->next;
// 	}
// }

static void		*send_data_to_client(void *sd)
{
	int	socket_fd;

	socket_fd = *(int *)sd;
	send_bots_to_client(socket_fd);

	// while (!g_vm->winner)
	// {
	// 	send(socket_fd, g_map, MEM_SIZE);
	// 	send_pixel_map_to_client(socket_fd);
	// 	send_other_data_to_client(socket_fd);
	// 	step();
	// }
	// send(socket_fd, vm->winner->id, 4, 0);
	return (sd);
}

void			send_data_all_clients(t_server *server)
{
	pthread_t	tid[4];
	int			i;

	i = -1;
	while (++i < server->n_client_sockets)
		if (server->client_sockets[i])
			pthread_create(&tid[i], NULL, send_data_to_client, &server->client_sockets[i]);
	i = -1;
	while (++i < server->n_client_sockets)
		if (server->client_sockets[i])
			pthread_join(tid[i], NULL);
}
