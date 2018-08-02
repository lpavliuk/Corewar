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

static void	connect_to_server(int socket_fd, char *ip)
{
	struct sockaddr_in	address;
	struct timeval		timeout;
	fd_set				set;

	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);
	if (!inet_aton(ip, &address.sin_addr))
		ft_error("Error");
	if (connect(socket_fd, (struct sockaddr *)&address, sizeof(address)))
		ft_error("Error: connect");
	FD_ZERO(&set);
    FD_SET(socket_fd, &set);
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	if (select(socket_fd + 1, &set, NULL, NULL, &timeout) != 1)	/* Checks whether we can read from this server socket or not. */
		ft_error("Error: connect");
}

static void				read_init_info(int socket_fd)
{
	char			flag_sec;
	unsigned char	str;

	flag_sec = 0;
	str = 0;
	while (1)
	{
		if (read(socket_fd, &str, sizeof(unsigned char)) > 0)
		{
			if (!flag_sec)
			{
				sleep(1);
				printf("Time to start the game: %d\n", str);
				flag_sec = 1;
				if (str == 0)
					break ;
			}
			else
			{
				printf("Number of connected players: %d\n", str);
				flag_sec = 0;
			}
		}
	}
}

// void				client(t_vm *vm, char *str)
// {
// 	int				socket_fd;

// 	socket_fd = create_socket();
// 	connect_to_server(socket_fd, vm->ip);
// 	send(socket_fd, str, ft_strlen(str), 0);
// 	read_init_info(socket_fd);
// 	while (1)
// 		;
// 	close(socket_fd);
// }

/*
** name | comment | exec
*/

static void				serialize(t_bot *bot, char *str)
{
	// int		str_len;

	// str_len = PROG_NAME_LENGTH + COMMENT_LENGTH + bot->size;
	// str = (unsigned char *)malloc(str_len);
	// (!str) ? ft_error("Error") : 0;
	
	strlcat(str, bot->name, PROG_NAME_LENGTH);
	strlcat(str + PROG_NAME_LENGTH, bot->comment, COMMENT_LENGTH);
	strlcat(str + PROG_NAME_LENGTH + COMMENT_LENGTH, (char *)bot->exec, bot->size);
	ft_printf("size: %d\n", bot->size);
}

/* End up version */

void					client(t_vm *vm)
{
	int				socket_fd;
	unsigned char	*data;
	unsigned char	str[PROG_NAME_LENGTH + COMMENT_LENGTH + vm->bot->size + 1];

	ft_bzero(str, PROG_NAME_LENGTH + COMMENT_LENGTH + vm->bot->size + 1);
	(vm->count_players != 1) ? ft_error("Error") : 0;
	serialize(vm->bot, (char *)str);
	socket_fd = create_socket();
	connect_to_server(socket_fd, vm->ip);
	send(socket_fd, "Ready to fight!", 15, 0);
	read_init_info(socket_fd);
	send(socket_fd, str, PROG_NAME_LENGTH + COMMENT_LENGTH + vm->bot->size, 0);
	int i = PROG_NAME_LENGTH + COMMENT_LENGTH;
	while (i < PROG_NAME_LENGTH + COMMENT_LENGTH + vm->bot->size)
		ft_printf("%x\n", str[i++]);
	while (1);
	close(socket_fd);
}
