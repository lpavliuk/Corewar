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
	new->nbr_cycles = 0;
	new->cur_cycle = 0;
	new->process_count = 0;
	new->port = 0;
	new->ip = NULL;
	new->winner = NULL;
	new->process = NULL;
	new->bot = NULL;
	return (new);
}

static char				is_uchar(char *s)
{
	int					num;
	unsigned char		i;

	num = 0;
	i = 0;
	while (ft_isdigit(s[i]) && i < 3)
		num = num * 10 + s[i++] - '0';
	return ((i == 0 || s[i] != '\0' || num > 255) ? 0 : 1);
}

static char				is_ushort(char *s)
{
	int					num;
	unsigned char		i;

	num = 0;
	i = 0;
	while (ft_isdigit(s[i]) && i < 6)
		num = num * 10 + s[i++] - '0';
	return ((i == 0 || s[i] != '\0' || num > 65535) ? 0 : 1);
}

static char				*get_ip(char *s)
{
	char				**octets;
	unsigned char		i;
	unsigned char		n_commas;

	(!(octets = ft_strsplit(s, '.'))) ? ft_error("Error") : 0;
	i = 0;
	while (octets[i])
		(!is_uchar(octets[i])) ? ft_error("Error") : ft_strdel(&octets[i++]);
	(i != 4) ? ft_error("Error") : free(octets);
	i = 0;
	n_commas = 0;
	while (s[i])
	{
		(s[i] == '.') ? (n_commas++) : 0;
		(n_commas > 3) ? ft_error("Error") : 0;
		i++;
	}
	return (s);
}

static unsigned short	get_port(char *s)
{
	if (!is_ushort(s) || ft_atoi(s) == 0)
		ft_error("Error");
	return ((unsigned short)ft_atoi(s));
}

void					get_info(t_vm *vm, char *args[], int argv, int *i)
{
	vm->flag_server = 1;
	(*i)++;
	if (*i >= argv)
		ft_error("Error");
	else
		vm->ip = get_ip(args[*i]);
	(*i)++;
	if (*i >= argv)
		ft_error("Error");
	else
		vm->port = get_port(args[*i]);
}



int		create_socket(void)
{
	int		socket_fd;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	(socket_fd < 0) ? ft_error("Error") : 0;
	return (socket_fd);
}

char	bind_to_address(int socket_fd, char *ip, unsigned short port)
{
	struct sockaddr_in	address;

	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	if (!inet_aton(ip, &address.sin_addr))
		ft_error("Error");
	return (bind(socket_fd, (struct sockaddr *)&address, sizeof(struct sockaddr_in)));
}

void	server(t_vm *vm)
{
	int		master_socket;
	int		client_socket_fd;
	char	*response;

	response = NULL;
	master_socket = create_socket();
	(bind_to_address(master_socket, vm->ip, vm->port)) ? ft_error("Error") : 0;
	listen(master_socket, 4);
	while (1)
	{
		client_socket_fd = accept(master_socket, NULL, NULL);
		if (!client_socket_fd)
			break ;
		get_next_line(client_socket_fd, &response);
		ft_printf("%s", response);
	}
	close(master_socket);
}

char	connect_to_server(int socket_fd, char *ip, unsigned short port)
{
	struct sockaddr_in	address;

	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	if (!inet_aton(ip, &address.sin_addr))
		ft_error("Error");
	return (connect(socket_fd, (struct sockaddr *)&address, sizeof(struct sockaddr_in)));
}

void	client(t_vm *vm)
{
	int		socket_fd;

	socket_fd = create_socket();
	(connect_to_server(socket_fd, vm->ip, vm->port) < 0) ? ft_error("Error") : 0;
	send(socket_fd, "Hello, World!\n", 14, 0);
	close(socket_fd);
}

void			get_args(t_vm *vm, int count, char **args)
{
	int				i;
	unsigned int	id;

	id = 0;
	i = 1;
	while (i < count)
	{
		if (ft_strequ(args[i], "-s"))
			get_info(vm, args, count, &i);
		else if (ft_strequ(args[i], "-c"))
			vm->flag_client = 1;
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_vm	*vm;

	vm = init_vm();
	get_args(vm, argc, argv);
	if (vm->flag_client)
		client(vm);
	else if (vm->flag_server)
		server(vm);
	return (0);
}
