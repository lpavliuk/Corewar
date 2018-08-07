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

static void	compute_speed(t_win *win, int key)
{
	if (key == KEY_Q || key == KEY_W)
	{
		if (key == KEY_Q && win->speed > 10)
			win->speed -= 10;
		else if (key == KEY_W && win->speed > 1)
			win->speed -= 1;
		else
			win->speed = 1;
	}
	else if (key == KEY_E || key == KEY_R)
	{
		if (key == KEY_R && win->speed < 990)
			win->speed += 10;
		else if (key == KEY_E && win->speed < 1000)
			win->speed += 1;
		else
			win->speed = 1000;
	}
	wattron(win->window, COLOR_PAIR(7) | A_BOLD);
	mvwprintw(win->window, CURSOR_Y + 2, CURSOR_X + win->sidebar_pad + 22,
	"%-4d", win->speed);
	wattroff(win->window, COLOR_PAIR(7) | A_BOLD);
}

static void	dispatcher_keys(t_win *win, int key)
{
	if (key == RESIZE)
		prepare_window(win);
	else if (key == KEY_SPACE)
	{
		if (win->paused)
		{
			nodelay(stdscr, true);
			win->paused = 0;
		}
		else
		{
			nodelay(stdscr, false);
			win->paused = 1;
		}
		show_status(win);
	}
	else if (key == KEY_Q || key == KEY_W || key == KEY_E || key == KEY_R)
		compute_speed(win, key);
}

void		redraw(t_win *win, int key)
{
	win->cursor_x = X_BEGIN;
	win->cursor_y = Y_BEGIN;
	if (key != -1)
		dispatcher_keys(win, key);
	if (!win->paused || key == KEY_S)
	{
		step();
		draw_map(win);
		show_sidebar(win);
		handle_pixels();
	}
	if (g_vm->winner)
	{
		print_winner(win);
		nodelay(stdscr, false);
	}
	wrefresh(win->window);
}
