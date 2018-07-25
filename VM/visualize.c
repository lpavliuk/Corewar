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

void	preparation()
{
	(!has_colors()) ? (endwin(), exit(0)) : start_color();
	init_color(COLOR_MAGENTA, 408, 408, 408);
	init_pair(6, COLOR_MAGENTA, COLOR_MAGENTA);			/* Layout color */
	init_pair(7, COLOR_WHITE, COLOR_BLACK);				/* Generic white color */
	/* PIXELS */
	init_pair(5, COLOR_BLACK, COLOR_BLACK);				/* Initial pixel color */
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
	wattron(win->window, COLOR_PAIR(6));
	wborder(win->window, c, c, c, c, c, c, c, c);
	mvwvline(win->window, 0, win->sidebar_pad, '*', win->height);
	wattroff(win->window, COLOR_PAIR(6));
}

void			draw_map(t_win *win, unsigned char cols)
{
	char			*base;
	unsigned short	i;

	i = 0;
	win->cursor_x = X_BEGIN;
	win->cursor_y = Y_BEGIN;
	base = "0123456789abcdef";
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

void	sidebar_initial(t_win *win, t_vm *vm, short *y, short x)
{
	mvwprintw(win->window, *y, x, "** %s **", ((win->paused) ? "PAUSED" : "RUNNING"));
	*y += 2;
	mvwprintw(win->window, *y, x, "Cycles/second limit : %d", win->speed);
	*y += 3;
	mvwprintw(win->window, *y, x, "Cycle : %d", vm->cur_cycle);
	*y += 2;
	mvwprintw(win->window, *y, x, "Processes : %d", vm->process_count);
	*y += 2;
}

void	sidebar_players(t_win *win, t_vm *vm, short *y, short x)
{
	unsigned char player_counter;
	t_bot	*bot;

	bot = vm->bot;
	player_counter = 1;
	while (bot)
	{
		mvwprintw(win->window, *y, x, "Player %d : ", (int)bot->player);
		wattron(win->window, COLOR_PAIR(player_counter));
		mvwprintw(win->window, (*y)++, x + 12, "%s", bot->name);
		wattroff(win->window, COLOR_PAIR(player_counter));
		mvwprintw(win->window, (*y)++, x, "  Last live : %21d", bot->last_live);
		mvwprintw(win->window, *y, x, "  Lives in current period : %7d", bot->lives_period);
		*y += 2;
		player_counter++;
		bot = bot->next;
	}
}

void	sidebar_statistics(t_win *win, t_vm *vm, short *y, short x)
{
	mvwprintw(win->window, (*y)++, x, "Live breakdown for current period : ");
	// show_line();
	(*y)++;
	mvwprintw(win->window, (*y)++, x, "Live breakdown for last period : ");
	// show_line();
	(*y)++;
}

void	sidebar_other(t_win *win, t_vm *vm, short *y, short x)
{
	mvwprintw(win->window, *y, x, "CYCLE_TO_DIE : %d", vm->cycle_to_die);
	*y += 2;
	mvwprintw(win->window, *y, x, "CYCLE_DELTA : %d", CYCLE_DELTA);
	*y += 2;
	mvwprintw(win->window, *y, x, "NBR_LIVE : %d", NBR_LIVE);
	*y += 2;
	mvwprintw(win->window, *y, x, "MAX_CHECKS : %d", MAX_CHECKS);
}

void	show_sidebar(t_win *win, t_vm *vm)
{
	short y;

	y = Y_BEGIN;
	wattron(win->window, COLOR_PAIR(7) | A_BOLD);
	sidebar_initial(win, vm, &y, win->sidebar_pad + X_BEGIN);
	sidebar_players(win, vm, &y, win->sidebar_pad + X_BEGIN);
	sidebar_statistics(win, vm, &y, win->sidebar_pad + X_BEGIN);
	sidebar_other(win, vm, &y, win->sidebar_pad + X_BEGIN);
	wattroff(win->window, COLOR_PAIR(7) | A_BOLD);
}

void	prepare_window(t_win *win, t_vm *vm)
{
	clear();
	draw_table(win);
	draw_map(win, 64);
	show_sidebar(win, vm);
	refresh();
	wrefresh(win->window);
}

void	compute_speed(int key, short int *speed)
{
	if (key == KEY_Q || key == KEY_W) /* q / w */
	{
		if (key == KEY_Q && *speed > 10)
			*speed -= 10;
		else if (key == KEY_W && *speed > 1)
			*speed -= 1;
		else
			*speed = 1;
	}
	else if (key == KEY_E || key == KEY_R) /* e / r */
	{
		if (key == KEY_R && *speed < 990)
			*speed += 10;
		else if (key == KEY_E && *speed < 1000)
			*speed += 1;
		else
			*speed = 1000;
	}
}

void	dispatcher(t_win *win, t_vm *vm, int key, char *flag)
{
	if (key == RESIZE)	/* RESIZE */
		prepare_window(win, vm);
	else if (key == KEY_SPACE)	/* SPACE */
	{
		if (!*flag)
		{
			*flag = 1;
			nodelay(stdscr, true);
		}
		else
		{
			*flag = 0;
			nodelay(stdscr, false);
		}
	}
	else if (key == KEY_Q || key == KEY_W || key == KEY_E || key == KEY_R)
		compute_speed(key, &win->speed);
}

void	redraw(t_win *win, t_vm *vm, int key)
{
	static char	flag = 0;

	// usleep(5000 - win->speed);
	dispatcher(win, vm, key, &flag);
	if (flag)
	{
		// step(vm);
		draw_map(win, 64);
		show_sidebar(win, vm);
		wrefresh(win->window);
	}
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
	prepare_window(win, vm);
	while ((key = getch()))
	{
		redraw(win, vm, key);
	}
	delwin(win->window);
	endwin();
}
