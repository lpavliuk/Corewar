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
#include <sys/select.h>
#include <pthread.h>
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

int		create_socket(void)
{
	int		socket_fd;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	(socket_fd < 0) ? ft_error("Error") : 0;
	return (socket_fd);
}

void	bzero_sockets(int sockets[], int n_sockets)
{
	int i;

	i = 0;
	while (i < n_sockets)
		sockets[i++] = 0;
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
	server->flag_start = 0;
	return (server);
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

void		add_sockets_to_set(t_server *server, int *max_sd)
{
	unsigned char	i;
	int				sd;

	i = 0;
	FD_ZERO(&server->read_fds);
	FD_SET(server->master_socket, &server->read_fds);
	*max_sd = server->master_socket;
	while (i < server->n_client_sockets)
	{
		sd = server->client_sockets[i];
		if (sd != 0)
		{
			FD_SET(sd, &server->read_fds);
			if (*max_sd < sd)
				*max_sd = sd;
		}
		i++;
	}
}

void		accept_client(t_server *server)
{
	unsigned char	i;
	int				new_socket;

	(server->count_players >= 4) ? ft_error("Error") : 0;
	new_socket = accept(server->master_socket, NULL, NULL);
	(!new_socket) ? ft_error("Error") : 0;
	i = 0;
	while (i < server->n_client_sockets)
	{
		if (server->client_sockets[i] == 0)
		{
			server->client_sockets[i] = new_socket;
			server->count_players++;
			return ;
		}
		i++;
	}
}

void		check_clients(t_server *server)
{
	unsigned char	buffer[12 + PROG_NAME_LENGTH + COMMENT_LENGTH + CHAMP_MAX_SIZE];
	unsigned char	i;
	int		sd;
	int		n_buffer;	

	i = 0;
	n_buffer = 12 + PROG_NAME_LENGTH + COMMENT_LENGTH + CHAMP_MAX_SIZE;
	while (i < server->n_client_sockets)
	{
		ft_bzero(buffer, n_buffer);
		sd = server->client_sockets[i];
		if (FD_ISSET(sd, &server->read_fds))
		{
			if ((read(sd, &buffer, n_buffer)) <= 0)
			{
				server->count_players--;
				server->client_sockets[i] = 0;
				close(sd);
			}
			else
			{

			}
		}
		i++;
	}
}

void		dispatcher_sockets(t_server *server)
{
	if (FD_ISSET(server->master_socket, &server->read_fds))	/* Someone wants to connect to the server. */
		accept_client(server);
	else
		check_clients(server);
}

void		*apply_clients(void *data)
{
	int				activity;
	t_server		*server;
	int				max_sd;		/* max socket descriptor. */
	struct timeval	timeout;

	timeout.tv_sec = 1;
	server = (t_server *)data;
	while (!server->flag_start)
	{
		max_sd = 0;
		add_sockets_to_set(server, &max_sd);
		activity = select(max_sd + 1, &server->read_fds, NULL, NULL, &timeout);
		(activity < 0) ? ft_error("Error: select") : 0;
		dispatcher_sockets(server);
	}
	(server->count_players == 0) ? ft_error("Error") : 0;
	return (data);
}

void		*check_command_start(void *server)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		if (ft_strequ(line, "START"))
		{
			ft_strdel(&line);
			((t_server *)server)->flag_start = 1;
			return (server);
		}
		else
			ft_strdel(&line);
	}
	return (server);
}

void			get_clients(t_server *server)
{
	pthread_t	tid[2];

	pthread_create(&tid[0], NULL, check_command_start, server);
	pthread_create(&tid[1], NULL, apply_clients, server);
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
}

/* >>>>>>>>>> SERVER <<<<<<<<<< */

void			server(t_vm *vm)
{
	t_server	*server;

	server = init_server();
	(bind_to_address(server->master_socket, vm->ip)) ? ft_error("Error") : 0;
	listen(server->master_socket, 4);
	get_clients(server);
	// close(master_socket);
}









/* >>>>>>>>>> CLIENT <<<<<<<<<< */

char	connect_to_server(int socket_fd, char *ip)
{
	struct sockaddr_in	address;

	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);
	if (!inet_aton(ip, &address.sin_addr))
		ft_error("Error");
	return (connect(socket_fd, (struct sockaddr *)&address, sizeof(struct sockaddr_in)));
}

/*
** name | comment | size | exec
*/

unsigned char	*serialize(t_bot *bot)
{
	unsigned char	*str;
	int		str_len;

	str_len = 12 + ft_strlen(bot->name) + ft_strlen(bot->comment) + size; /* We specify 4 bytes which correspond strlen(name), 4 bytes - strlen(comment), 4 bytes - length of size var. */
	str = (unsigned char *)malloc(str_len);
	(!str) ? ft_error("Error") : 0;
	ft_bzero(str, str_len);
	strncat(str, ft_strlen(bot->name), 4);
	strncat(str, bot->name, ft_strlen(bot->name));
	strncat(str, ft_strlen(bot->comment), 4);
	strncat(str, bot->comment, ft_strlen(bot->comment));
	strncat(str, size, 4);
	strncat(str, bot->exec, size);
	return (str);
}

void	client(t_vm *vm, char *str)
{
	int		socket_fd;
	unsigned char	*data;

	(vm->count_players != 1) ? ft_error("Error") : 0;
	data = serialize(vm->bot);
	socket_fd = create_socket();
	(connect_to_server(socket_fd, vm->ip) < 0) ? ft_error("Error") : 0;
	send(socket_fd, data, strlen(data), 0);
	close(socket_fd);
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
