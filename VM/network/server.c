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

static void			bzero_sockets(int sockets[], int n_sockets)
{
	int				i;

	i = 0;
	while (i < n_sockets)
		sockets[i++] = 0;
}

static t_server		*init_server(void)
{
	t_server		*server;

	server = (t_server *)malloc(sizeof(t_server));
	(!server) ? ft_error("Error: init_server()") : 0;
	server->master_socket = create_socket();
	server->n_client_sockets = 4;
	bzero_sockets(server->client_sockets, server->n_client_sockets);
	server->flag_start = 0;
	return (server);
}

static char				bind_to_address(int socket_fd, char *ip)
{
	struct sockaddr_in	address;

	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);
	if (!inet_aton(ip, &address.sin_addr))
		ft_error("Error: inet_aton()");
	return (bind(socket_fd, (struct sockaddr *)&address, sizeof(struct sockaddr_in)));
}

void					server(void)
{
	t_server			*server;

	server = init_server();
	(bind_to_address(server->master_socket, g_vm->ip)) ? ft_error("Error: bind()") : 0;
	listen(server->master_socket, 1);
	get_clients(server);

	get_clients_exec(server);
	while (g_vm->bot)
	{
		ft_printf("name: %s\ncomment: %s\n", g_vm->bot->name, g_vm->bot->comment);
		print_memory(g_vm->bot->exec, g_vm->bot->size);
		g_vm->bot = g_vm->bot->next;
	}
	while (1);

	// fill_map(vm, vm->count_players);
	// start_game(server);
	// close(master_socket);
}
