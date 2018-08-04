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

static void		fill_map(void)
{
	t_bot			*bot;
	unsigned int	i;
	unsigned int	total;

	total = 0;
	bot = g_vm->bot;
	while (bot)
	{
		i = 0;
		push_new_process(&g_vm->process, &g_vm->process_count, bot, total + i);
		while (i < bot->size)
		{
			g_map[total + i] = bot->exec[i];
			i++;
		}
		total += MEM_SIZE / g_vm->count_players;
		bot = bot->next;
	}
}

/*---------------------------------------------------------------*/

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

	// t_bot	*bot = g_vm->bot;
	// while (bot)
	// {
	// 	ft_printf("name: %s\ncomment: %s\n size: %d\n", bot->name, bot->comment, bot->size);
	// 	print_memory(bot->exec, bot->size);
	// 	bot = bot->next;
	// }
	// ft_printf("\n\n");

	fill_map();
	create_pixel_map();
	start_game(server);
	while (1)
		;
	// close(master_socket);
}
