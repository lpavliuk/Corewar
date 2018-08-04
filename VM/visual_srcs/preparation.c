/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 14:03:16 by tkiselev          #+#    #+#             */
/*   Updated: 2018/07/19 14:03:20 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_win		*init_win(void)
{
	t_win	*win;

	win = (t_win *)malloc(sizeof(t_win));
	(!win) ? (endwin(), exit(0)) : 0;
	win->height = 68;
	win->width = 254;
	win->sidebar_pad = 196;
	win->window = NULL;
	win->speed = 50;
	win->paused = 1;
	return (win);
}

void			ft_prepare_pixel_map(void)
{
	unsigned short	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		g_pixels[i] = (t_pixel *)malloc(sizeof(t_pixel));
		(!g_pixels[i]) ? ft_error("Error") : 0;
		g_pixels[i]->counter = 0;
		g_pixels[i]->color = INIT_PIXEL_COLOR;
		i++;
	}
}

static void		fill_pixel_map(t_bot *bot, char count_players)
{
	unsigned int	i;
	unsigned int	total;
	unsigned char	bot_counter;

	total = 0;
	bot_counter = 1;
	while (bot)
	{
		i = 0;
		while (i < bot->size)
		{
			g_pixels[total + i]->color = bot_counter;
			i++;
		}
		g_pixels[total]->color = bot_counter + 20;
		total += MEM_SIZE / count_players;
		bot_counter++;
		bot = bot->next;
	}
}

void			create_pixel_map(void)
{
	g_pixels = (t_pixel **)malloc(sizeof(t_pixel *) * MEM_SIZE);
	(!g_pixels) ? ft_error("Error") : ft_prepare_pixel_map();
	fill_pixel_map(g_vm->bot, g_vm->count_players);
}

void			color_preparation(void)
{
	curs_set(0);
	(!has_colors()) ? (endwin(), exit(0)) : start_color();
	init_color(COLOR_MAGENTA, 408, 408, 408);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);				/* First bot */
	init_pair(2, COLOR_BLUE, COLOR_BLACK);				/* Second bot */
	init_pair(3, COLOR_RED, COLOR_BLACK);				/* Third bot */
	init_pair(4, COLOR_CYAN, COLOR_BLACK);				/* Fourth bot */
	init_pair(5, COLOR_BLACK, COLOR_BLACK);				/* Initial pixel color */

	/* ----- LIVE ----- */
	init_pair(11, COLOR_WHITE, COLOR_GREEN);
	init_pair(12, COLOR_WHITE, COLOR_BLUE);
	init_pair(13, COLOR_WHITE, COLOR_RED);
	init_pair(14, COLOR_WHITE, COLOR_CYAN);

	/* ----- PROCESSES ----- */
	init_pair(21, COLOR_BLACK, COLOR_GREEN);
	init_pair(22, COLOR_BLACK, COLOR_BLUE);
	init_pair(23, COLOR_BLACK, COLOR_RED);
	init_pair(24, COLOR_BLACK, COLOR_CYAN);
	init_pair(25, COLOR_BLACK, COLOR_BLACK);

	/* ----- OTHERS ----- */
	init_pair(6, COLOR_MAGENTA, COLOR_MAGENTA);			/* Layout color */	// WTF???
	init_pair(7, COLOR_WHITE, COLOR_BLACK);				/* Generic white color */
	init_pair(8, COLOR_RED, COLOR_BLACK);				/* Status: paused */
	init_pair(9, COLOR_GREEN, COLOR_BLACK);				/* Status: running */
}
