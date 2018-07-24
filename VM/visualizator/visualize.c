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
	win->cursor_y = Y_BEGIN;
	win->cursor_x = X_BEGIN;
	win->sidebar_pad = 196;
	win->window = NULL;
	return (win);
}

void	preparation()
{
	(!has_colors()) ? (endwin(), exit(0)) : start_color();
	init_pair(8, COLOR_MAGENTA, COLOR_MAGENTA);
	init_color(COLOR_PAIR(8), 408, 408, 408);
	init_pair(9, COLOR_MAGENTA, COLOR_BLACK);
}

void	draw_table(t_win *win)
{
	char	c;

	c = '*';
	win->window = newwin(win->height, win->width, 0, 0);
	(!win->window) ? (endwin(), exit(0)) : 0;
	wattron(win->window, COLOR_PAIR(8));
	wborder(win->window, c, c, c, c, c, c, c, c);
	mvwvline(win->window, 0, win->sidebar_pad, '*', win->height);
	wattroff(win->window, COLOR_PAIR(8));
}

void			draw_map(t_win *win, t_vm *vm, unsigned int cols)
{
	char			*base = "0123456789abcdef";
	unsigned int	i;

	i = 0;
	wattron(win->window, A_BOLD);
	wattron(win->window, COLOR_PAIR(9));
	while (i < MEM_SIZE)
	{
		mvwaddch(win->window, win->cursor_y, win->cursor_x++, base[vm->map[i] / 16]);
		mvwaddch(win->window, win->cursor_y, win->cursor_x++, base[vm->map[i] % 16]);
		i++;
		if ((i % cols) == 0)
		{
			win->cursor_x = X_BEGIN;
			win->cursor_y++;
		}
		else
			mvwaddch(win->window, win->cursor_y, win->cursor_x++, ' ');
	}
	// wattroff(win->window, A_BOLD);
	wattroff(win->window, COLOR_PAIR(9));
}

void	output_window(t_win *win, t_vm *vm)
{
	clear();
	draw_table(win);
	draw_map(win, vm, 64);
	refresh();
	wrefresh(win->window);
}

void	visualize(t_vm *vm)
{
	t_win	*win;
	int		key;	/* For getch(). */

	key = 0;
	initscr();
	noecho();
	preparation();
	win = init_win();
	output_window(win, vm);
	while ((key = getch()))
	{
		delwin(win->window);
		win->cursor_x = X_BEGIN;
		win->cursor_y = Y_BEGIN;
		output_window(win, vm);
	}
	delwin(win->window);
	endwin();
}
