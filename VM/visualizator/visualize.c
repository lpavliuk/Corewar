/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 16:02:56 by tkiselev          #+#    #+#             */
/*   Updated: 2018/07/22 16:02:58 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualize.h"

t_win		*init_win(void)
{
	t_win	*win;

	win = (t_win *)malloc(sizeof(t_win));
	(!win) ? (endwin(), exit(0)) : 0;
	win->height = 68;
	win->width = 254;
	win->sidebar_pad = 196;
	win->window = NULL;
	return (win);
}

void	preparation()
{
	(!has_colors()) ? (endwin(), exit(0)) : start_color();
	init_color(COLOR_MAGENTA, 408, 408, 408);
	init_pair(6, COLOR_MAGENTA, COLOR_MAGENTA);			/* Layout color */
	/* PIXELS */
	init_pair(5, COLOR_BLACK, COLOR_BLACK);					/* Initial pixel color */
	init_pair(1, COLOR_GREEN, COLOR_BLACK);				/* First bot */
	init_pair(2, COLOR_BLUE, COLOR_BLACK);				/* Second bot */
	init_pair(3, COLOR_RED, COLOR_BLACK);				/* Third bot */
	init_pair(4, COLOR_CYAN, COLOR_BLACK);				/* Fourth bot */
}

void	draw_table(t_win *win)
{
	char	c;

	c = '*';
	win->window = newwin(win->height, win->width, 0, 0);
	if (!win->window)
	{
		endwin();
		exit(0);
	}
	wattron(win->window, COLOR_LAYOUT);
	wborder(win->window, c, c, c, c, c, c, c, c);
	mvwvline(win->window, 0, win->sidebar_pad, '*', win->height);
	wattroff(win->window, COLOR_LAYOUT);
}

void			draw_map(t_win *win, unsigned char cols)
{
	char			*base = "0123456789abcdef";
	unsigned short	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		wattron(win->window, COLOR_PAIR(g_map[i].color));
		(g_map[i].color == 5) ? (wattron(win->window, A_BOLD)) : 0;
		mvwaddch(win->window, win->cursor_y, win->cursor_x++, base[g_map[i].value / 16]);
		mvwaddch(win->window, win->cursor_y, win->cursor_x++, base[g_map[i].value % 16]);
		(g_map[i].color == 5) ? (wattroff(win->window, A_BOLD)) : 0;
		wattroff(win->window, COLOR_PAIR(g_map[i].color));
		i++;
		if ((i % cols) == 0)
		{
			win->cursor_y++;
			win->cursor_x = X_BEGIN;
		}
		else
			mvwaddch(win->window, win->cursor_y, win->cursor_x++, ' ');
	}
}

void	output_window(t_win *win)
{
	clear();
	win->cursor_x = X_BEGIN;
	win->cursor_y = Y_BEGIN;
	draw_table(win);
	draw_map(win, 64);

	refresh();
	wrefresh(win->window);
}

void	visualize(t_vm *vm)
{
	t_win	*win;
	int		key;

	key = 0;
	initscr();
	noecho();
	preparation();
	win = init_win();
	output_window(win);
	while ((key = getch()))
	{
		delwin(win->window);
		output_window(win);
	}
	delwin(win->window);
	endwin();
}
