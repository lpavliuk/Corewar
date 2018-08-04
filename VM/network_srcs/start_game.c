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

static void		*send_map(void *sd)
{
	int socket_sd;

	socket_sd = *(int *)sd;
	send(socket_sd, g_map, MEM_SIZE, 0);
	return (sd);
}

static void		send_map_all_clients(t_server *server)
{
	pthread_t	tid[4];
	int			i;

	i = -1;
	while (++i < server->n_client_sockets)
		if (server->client_sockets[i])
			pthread_create(&tid[i], NULL, send_map, &server->client_sockets[i]);
	i = -1;
	while (++i < server->n_client_sockets)
		if (server->client_sockets[i])
			pthread_join(tid[i], NULL);
}

void			start_game(t_server *server)
{
	send_map_all_clients(server);
}
