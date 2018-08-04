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

void	send_map(int sd)
{
	
}

void	send_map_all_clients(t_server *server)
{
	pthread_t	tid[server->n_client_sockets];
	int			i;
	int			sd;

	i = -1;
	while (++i < server->n_client_sockets)
	{
		sd = server->client_sockets[i];
		pthread_creat(&tid[i], NULL, send_map, sd);
	}
	i = -1;
	while (++i < server->n_client_sockets)
		pthread_join(tid[i], NULL);
}

void	start_game(t_server *server)
{
	send_map_all_clients(server);
}
