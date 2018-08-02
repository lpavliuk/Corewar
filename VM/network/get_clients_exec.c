/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_clients_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 18:11:43 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/01 18:11:44 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		get_clients_exec(t_vm *vm, t_server *server)
{
	int i;
	int sd;
	unsigned int id_bot;
    t_bot *new_bot;

	i = 0;
	id_bot = 1;
	while (i < server->n_client_sockets)
	{
		sd = server->client_sockets[i];
		if (sd > 0)
		{
			new_bot = push_new_bot(&vm->bot, id_bot);
			new_bot->exec = (unsigned char *)malloc(CHAMP_MAX_SIZE + 1);
			ft_bzero(new_bot->exec, CHAMP_MAX_SIZE);
			read(sd, &new_bot->name, PROG_NAME_LENGTH);
			read(sd, &new_bot->comment, COMMENT_LENGTH);
			read(sd, new_bot->exec, 38);
		}
		i++;
	}
}
