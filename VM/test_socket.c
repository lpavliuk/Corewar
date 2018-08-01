/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_socket.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 19:38:09 by opavliuk          #+#    #+#             */
/*   Updated: 2018/07/30 19:38:10 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/time.h>
#include "corewar.h"

static t_vm		*init_vm(void)
{
	t_vm	*new;

	if (!(new = (t_vm *)malloc(sizeof(t_vm))))
		exit(0);
	ft_bzero(g_map, MEM_SIZE);
	new->count_players = 0;
	new->flag_visual = 0;
	new->flag_dump = 0;
	new->flag_server = 0;
	new->flag_client = 0;
	new->cycle_to_die = CYCLE_TO_DIE;
	new->dump_cycles = 0;
	new->cur_cycle = 0;
	new->process_count = 0;
	new->port = 0;
	new->ip = NULL;
	new->winner = NULL;
	new->process = NULL;
	new->bot = NULL;
	return (new);
}

static void					get_info_server(t_vm *vm, char *args[], int argv, int *i)
{
	vm->flag_server = 1;
	(*i)++;
	if (*i >= argv)
		ft_error("Error");
	else
		vm->ip = args[*i];
}

static void					get_info_client(t_vm *vm, char *args[], int argv, int *i)
{
	vm->flag_client = 1;
	(*i)++;
	if (*i >= argv)
		ft_error("Error");
	else
		vm->ip = args[*i];
}

void	bzero_sockets(int sockets[], int n_sockets)
{
	int i;

	i = 0;
	while (i < n_sockets)
		sockets[i++] = 0;
}

int		create_socket(void)
{
	int		socket_fd;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	(socket_fd < 0) ? ft_error("Error") : 0;
	return (socket_fd);
}

char	bind_to_address(int socket_fd, char *ip)
{
	struct sockaddr_in	address;

	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);
	if (!inet_aton(ip, &address.sin_addr))
		ft_error("Error");
	return (bind(socket_fd, (struct sockaddr *)&address, sizeof(struct sockaddr_in)));
}

void	get_clients(int master_socket, int client_sockets[], int n_client_sockets, fd_set read_fds)
{
	char	*line;
	int		new_socket;

	/* Here i need to implement timeout function */
	line = NULL;
	while (!ft_strequ(line, "GAME"))
	{
		new_socket = accept(master_socket, NULL, NULL);

		get_next_line(0, &line);	/* In order to track whether 'GAME' command has been written. */
	}
	(!server->count_players) ? ft_error("Error") : ft_strdel(&line);
}

t_server	*init_server(void)
{
	t_server	*server;

	server = (t_server *)malloc(sizeof(t_server));
	(!server) ? ft_error("Error") : 0;
	server->master_socket = create_socket();
	server->n_client_sockets = 4;
	bzero_sockets(server->client_sockets, server->n_client_sockets);
	server->count_players = 0;
	return (server);
}

void	server(t_vm *vm)
{
	t_server	*server;

	server = init_server();

	// (bind_to_address(server->master_socket, vm->ip)) ? ft_error("Error") : 0;
	// listen(server->master_socket, 4);

	// get_clients(server, vm);

	// close(master_socket);
}

char	connect_to_server(int socket_fd, char *ip)
{
	struct sockaddr_in	address;

	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);
	if (!inet_aton(ip, &address.sin_addr))
		ft_error("Error");
	return (connect(socket_fd, (struct sockaddr *)&address, sizeof(struct sockaddr_in)));
}

void	client(t_vm *vm, char *str)
{
	int		socket_fd;

	socket_fd = create_socket();
	(connect_to_server(socket_fd, vm->ip) < 0) ? ft_error("Error") : 0;
	send(socket_fd, str, strlen(str), 0);
}








void			get_args(t_vm *vm, int count, char **args)
{
	int				i;

	i = 1;
	while (i < count)
	{
		if (ft_strequ(args[i], "-s"))
			get_info_server(vm, args, count, &i);
		else if (ft_strequ(args[i], "-c"))
			get_info_client(vm, args, count, &i);
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_vm	*vm;

	vm = init_vm();
	get_args(vm, argc, argv);

	if (vm->flag_client && vm->flag_server)
		ft_error("Error");
	else if (vm->flag_client)
		client(vm, argv[1]);
	else if (vm->flag_server)
		server(vm);
	return (0);
}
