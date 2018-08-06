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

inline static void	get_data_select(int socket_fd, fd_set read_fds, void *dest, int len)
{
	if (select(socket_fd + 1, &read_fds, NULL, NULL, NULL) > 0)
	{
		if (recv(socket_fd, dest, len, 0) <= 0)
			ft_error("Error: connection interrupted");
	}
	else
		ft_error("Error: connection interrupted");
}

static void	get_pixel_map(int socket_fd, fd_set read_fds)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
		get_data_select(socket_fd, read_fds, g_pixels[i++], 2);
}

static void	get_init_data(int socket_fd, fd_set read_fds)
{
	t_bot			*bot;
	unsigned int	bot_id;
	unsigned char	player_counter;

	bot_id = -1;
	player_counter = 1;
	get_data_select(socket_fd, read_fds, &g_vm->count_players, 1);
	while (player_counter <= g_vm->count_players)
	{
		bot = push_new_bot(&g_vm->bot, bot_id);
		bot->player_counter = player_counter;
		get_data_select(socket_fd, read_fds, bot->name, PROG_NAME_LENGTH);
		get_data_select(socket_fd, read_fds, bot->comment, COMMENT_LENGTH);
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

static void		get_other_data(int socket_fd, fd_set read_fds)
{
	t_bot	*bot;

	get_data_select(socket_fd, read_fds, &g_vm->cycle_to_die, 4);
	get_data_select(socket_fd, read_fds, &g_vm->cur_cycle, 4);
	get_data_select(socket_fd, read_fds, &g_vm->process_count, 4);
	bot = g_vm->bot;
	while (bot)
	{
		get_data_select(socket_fd, read_fds, &bot->lives_cur_period, 4);
		get_data_select(socket_fd, read_fds, &bot->lives_last_period, 4);
		get_data_select(socket_fd, read_fds, &bot->last_live, 4);
		bot = bot->next;
	}
}

static void	get_winner(unsigned int winner_id)
{
	t_bot	*bot;

	bot = g_vm->bot;
	while (bot)
	{
		if (bot->id == winner_id)
		{
			g_vm->winner = bot;
			return ;
		}
		bot = bot->next;
	}
}

// void	prohodochka(void)
// {
// 	ft_printf("count players = %d\n", g_vm->count_players);
// 	while (g_vm->bot)
// 	{
// 		ft_printf("player: %d\nname: %s\ncomment: %s\nid: %d\n", g_vm->bot->player_counter, g_vm->bot->name, g_vm->bot->comment, g_vm->bot->id);
// 		ft_printf("lives_cur_period: %u\nlives_last_period: %u\nlast_live: %u\n", g_vm->bot->lives_cur_period, g_vm->bot->lives_last_period, g_vm->bot->last_live);
// 		g_vm->bot = g_vm->bot->next;
// 	}
// 	print_memory(g_map, MEM_SIZE);
// 	int i = -1;
// 	while (++i < MEM_SIZE)
// 		ft_printf("counter: %d | color %d\n", g_pixels[i]->counter, g_pixels[i]->color);
// 	ft_printf("cycle_to_die: %u\n", g_vm->cycle_to_die);
// 	ft_printf("cur_cycle: %u\n", g_vm->cur_cycle);
// 	ft_printf("process_count: %u\n", g_vm->process_count);
// }

void	get_game(int socket_fd, fd_set read_fds)
{
	unsigned int winner_id;

	winner_id = 0;
	remove_player(&g_vm->bot);	/* KOSTIL */
	get_init_data(socket_fd, read_fds);
	create_pixel_map();
	while (!winner_id)
	{
		get_data_select(socket_fd, read_fds, g_map, MEM_SIZE);
		get_pixel_map(socket_fd, read_fds);
		get_other_data(socket_fd, read_fds);
		get_data_select(socket_fd, read_fds, &winner_id, 4);
		// prohodochka();
		while (1);
	}
	get_winner(winner_id);
}
