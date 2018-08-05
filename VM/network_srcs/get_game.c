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

static void	get_pixel_map(int socket_fd)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (recv(socket_fd, g_pixels[i], 2, 0) < 0)
			ft_error("Error: get_pixel_map()");
		i++;
	}
}

static void	get_init_data(int socket_fd)
{
	t_bot			*bot;
	unsigned int	bot_id;
	unsigned char	player_counter;

	bot_id = -1;
	player_counter = 1;
	read(socket_fd, &g_vm->count_players, 1);
	while (player_counter <= g_vm->count_players)
	{
		bot = push_new_bot(&g_vm->bot, bot_id);
		bot->player_counter = player_counter;
		read(socket_fd, bot->name, PROG_NAME_LENGTH);
		read(socket_fd, bot->comment, COMMENT_LENGTH);
		bot_id--;
		player_counter++;
	}
}

static void		remove_player(t_bot **bot)
{
	ft_strdel((char **)&(*bot)->exec);
	free(*bot);
	*bot = NULL;
}

void	get_game(int socket_fd, fd_set read_fds)
{
	remove_player(&g_vm->bot);	/* KOSTIL */
	get_init_data(socket_fd);

	// t_bot *bot = g_vm->bot;
	// while (bot)
	// {
	// 	ft_printf("\nPLAYER %d\n", bot->player_counter);
	// 	ft_printf("id = %u\n", bot->id);
	// 	ft_printf("name = %s\n", bot->name);
	// 	ft_printf("comment = %s\n", bot->comment);
	// 	bot = bot->next;
	// }




	// create_pixel_map();
	// while (select(socket_fd + 1, &read_fds, NULL, NULL, NULL) > 0)
	// {
	// 	if (recv(socket_fd, &g_map, MEM_SIZE, 0) <= 0)
	// 		ft_error("Error: get_game()");
	// 	get_pixel_map(socket_fd, read_fds);
	// }
}
