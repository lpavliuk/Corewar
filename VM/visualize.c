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
	win->cursor_x = X_BEGIN;
	win->cursor_y = Y_BEGIN;
	win->window = NULL;
	win->speed = 50;
	win->paused = 1;
	return (win);
}

void	preparation()
{
	(!has_colors()) ? (endwin(), exit(0)) : start_color();
	init_color(COLOR_MAGENTA, 408, 408, 408);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);				/* First bot */
	init_pair(2, COLOR_BLUE, COLOR_BLACK);				/* Second bot */
	init_pair(3, COLOR_RED, COLOR_BLACK);				/* Third bot */
	init_pair(4, COLOR_CYAN, COLOR_BLACK);				/* Fourth bot */
	init_pair(5, COLOR_BLACK, COLOR_BLACK);				/* Initial pixel color */
	init_pair(6, COLOR_MAGENTA, COLOR_MAGENTA);			/* Layout color */
	init_pair(7, COLOR_WHITE, COLOR_BLACK);				/* Generic white color */
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

void	sidebar_initial(t_win *win, t_vm *vm)
{
	mvwprintw(win->window, CURSOR_Y, CURSOR_X, "** %s **", ((win->paused) ? "PAUSED" : "RUNNING"));
	CURSOR_Y += 2;
	mvwprintw(win->window, CURSOR_Y, CURSOR_X, "Cycles/second limit : %d", win->speed);
	CURSOR_Y += 3;
	mvwprintw(win->window, CURSOR_Y, CURSOR_X, "Cycle : %d", vm->cur_cycle);
	CURSOR_Y += 2;
	mvwprintw(win->window, CURSOR_Y, CURSOR_X, "Processes : %d", vm->process_count);
	CURSOR_Y += 2;
}

void	sidebar_players(t_win *win, t_vm *vm)
{
	t_bot	*bot;

	bot = vm->bot;
	while (bot)
	{
		mvwprintw(win->window, CURSOR_Y, CURSOR_X, "Player %d : ", (int)bot->id);
		wattron(win->window, COLOR_PAIR(bot->player_counter));
		mvwprintw(win->window, CURSOR_Y, CURSOR_X + 12, "%s", bot->name);
		CURSOR_Y++;
		wattroff(win->window, COLOR_PAIR(bot->player_counter));
		mvwprintw(win->window, CURSOR_Y, CURSOR_X, "  Last live : %21d", bot->last_live);
		CURSOR_Y++;
		mvwprintw(win->window, CURSOR_Y, CURSOR_X, "  Lives in current period : %7d", bot->lives_cur_period);
		CURSOR_Y += 2;
		bot = bot->next;
	}
}

/*
** This function returns cost of one live.
*/

double		get_cost_live(t_bot *bot, char len, char flag)
{
	double	res;

	res = 0;
	while (bot)
	{
		if (flag == CURR_PERIOD)
			res += bot->lives_cur_period;
		else if (flag == LAST_PERIOD)
			res += bot->lives_last_period;
		bot = bot->next;
	}
	return (len / res);
}

void	show_line(t_win *win, t_bot *bot, char flag)
{
	double			cost_live;
	int				tmp;		/* How much area certain player occupies. */
	char			len;		/* Whole area. */

	len = 50;
	cost_live = get_cost_live(bot, len, flag);
	mvwaddch(win->window, CURSOR_Y, CURSOR_X, '[');
	CURSOR_X++;
	mvwaddch(win->window, CURSOR_Y, CURSOR_X + len, ']');
	while (len > 0)
		mvwaddch(win->window, CURSOR_Y, CURSOR_X + --len, '-');
	while (bot)
	{
		tmp = cost_live * bot->lives_cur_period;
		wattron(win->window, COLOR_PAIR(bot->player_counter));
		while (tmp > 0)
		{
			mvwaddch(win->window, CURSOR_Y, CURSOR_X, '-');
			CURSOR_X++;
			tmp--;
		}
		wattroff(win->window, COLOR_PAIR(bot->player_counter));
		bot = bot->next;
	}
	CURSOR_X = win->sidebar_pad + X_BEGIN;
}

void	sidebar_statistics(t_win *win, t_vm *vm)
{
	mvwprintw(win->window, CURSOR_Y, CURSOR_X, "Live breakdown for current period : ");
	CURSOR_Y++;
	wattron(win->window, COLOR_PAIR(5));
	show_line(win, vm->bot, CURR_PERIOD);
	wattroff(win->window, COLOR_PAIR(5));
	CURSOR_Y += 2;
	mvwprintw(win->window, CURSOR_Y, CURSOR_X, "Live breakdown for last period : ");
	CURSOR_Y++;
	wattron(win->window, COLOR_PAIR(5));
	show_line(win, vm->bot, LAST_PERIOD);
	wattroff(win->window, COLOR_PAIR(5));
	CURSOR_Y += 2;
}

void	sidebar_other(t_win *win, t_vm *vm)
{
	mvwprintw(win->window, CURSOR_Y, CURSOR_X, "CYCLE_TO_DIE : %d", vm->cycle_to_die);
	CURSOR_Y += 2;
	mvwprintw(win->window, CURSOR_Y, CURSOR_X, "CYCLE_DELTA : %d", CYCLE_DELTA);
	CURSOR_Y += 2;
	mvwprintw(win->window, CURSOR_Y, CURSOR_X, "NBR_LIVE : %d", NBR_LIVE);
	CURSOR_Y += 2;
	mvwprintw(win->window, CURSOR_Y, CURSOR_X, "MAX_CHECKS : %d", MAX_CHECKS);
}

void	show_sidebar(t_win *win, t_vm *vm)
{
	win->cursor_y = Y_BEGIN;
	win->cursor_x = win->sidebar_pad + X_BEGIN;

	wattron(win->window, COLOR_PAIR(7) | A_BOLD);

	sidebar_initial(win, vm);
	sidebar_players(win, vm);
	sidebar_statistics(win, vm);
	sidebar_other(win, vm);

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
	{
		compute_speed(key, &win->speed);
		wattron(win->window, COLOR_PAIR(7) | A_BOLD);
		mvwprintw(win->window, CURSOR_Y + 2, CURSOR_X + win->sidebar_pad + 22, "%-4d", win->speed);
		wattroff(win->window, COLOR_PAIR(7) | A_BOLD);
	}
}

void	redraw(t_win *win, t_vm *vm, int key)
{
	static char	flag = 0;

	// usleep(5000 - win->speed);
	win->cursor_x = X_BEGIN;
	win->cursor_y = Y_BEGIN;
	dispatcher(win, vm, key, &flag);
	if (flag)
	{
		// step(vm);
		draw_map(win, 64);
		show_sidebar(win, vm);
	}
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
	prepare_window(win, vm);
	while ((key = getch()))
	{
		redraw(win, vm, key);
	}
	delwin(win->window);
	endwin();
}
