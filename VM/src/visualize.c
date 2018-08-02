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

/*
** Color 5 because it is an initial number that represents the color of pixel.
*/

void		ft_bzero_pixel_map(void)
{
	unsigned short	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		g_pixels[i] = (t_pixel *)malloc(sizeof(t_pixel));
		(!g_pixels[i]) ? ft_error("Error") : 0;
		g_pixels[i]->counter = 0;
		g_pixels[i]->color = 5;
		g_pixels[i]->bold = 0;
		g_pixels[i]->live = 0;
		g_pixels[i]->empty = 1;
		i++;
	}
}

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

void	preparation(void)
{
	curs_set(0);
	(!has_colors()) ? (endwin(), exit(0)) : start_color();
	init_color(COLOR_MAGENTA, 408, 408, 408);
	/* BOT COLORS */
	init_pair(1, COLOR_GREEN, COLOR_BLACK);				/* First bot */
	init_pair(2, COLOR_BLUE, COLOR_BLACK);				/* Second bot */
	init_pair(3, COLOR_RED, COLOR_BLACK);				/* Third bot */
	init_pair(4, COLOR_CYAN, COLOR_BLACK);				/* Fourth bot */
	/* PROCESS COLORS */
	init_pair(11, COLOR_WHITE, COLOR_GREEN);
	init_pair(12, COLOR_WHITE, COLOR_BLUE);
	init_pair(13, COLOR_WHITE, COLOR_RED);
	init_pair(14, COLOR_WHITE, COLOR_CYAN);
	init_pair(15, COLOR_BLACK, COLOR_BLACK);
	/* LIVE */
	init_pair(21, COLOR_WHITE, COLOR_GREEN);
	init_pair(22, COLOR_WHITE, COLOR_BLUE);
	init_pair(23, COLOR_WHITE, COLOR_RED);
	init_pair(24, COLOR_WHITE, COLOR_CYAN);
	/* OTHERS */
	init_pair(5, COLOR_BLACK, COLOR_BLACK);				/* Initial pixel color */
	init_pair(6, COLOR_MAGENTA, COLOR_MAGENTA);			/* Layout color */
	init_pair(7, COLOR_WHITE, COLOR_BLACK);				/* Generic white color */
	init_pair(8, COLOR_RED, COLOR_BLACK);				/* Status: paused */
	init_pair(9, COLOR_GREEN, COLOR_BLACK);				/* Status: running */
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

void			show_processes(t_win *win, t_vm *vm, unsigned char cols, char *base)
{
	t_process		*process;
	unsigned char	y;
	unsigned char	x;

	process = vm->process;
	while (process)
	{
		y = Y_BEGIN + (process->position / cols);
		x = process->position % cols;
		x = X_BEGIN + x * 3;
		wattron(win->window, COLOR_PAIR(g_pixels[process->position]->color) | A_REVERSE);
		mvwaddch(win->window, y, x, base[g_map[process->position] / 16]);
		mvwaddch(win->window, y, x + 1, base[g_map[process->position] % 16]);
		wattroff(win->window, COLOR_PAIR(g_pixels[process->position]->color) | A_REVERSE);
		process = process->next;
	}
}

void		attributes_action(WINDOW *window, t_pixel *pixel, char flag)
{
	if (flag == ON)
	{
		wattron(window, COLOR_PAIR(pixel->color));
		if (pixel->empty)
			wattron(window, A_BOLD);
		else if (pixel->live)
		{
			wattron(window, COLOR_PAIR(pixel->color + LIVE_COLOR) | A_BOLD);
			pixel->counter--;
			(pixel->counter <= 0) ? (pixel->live = 0) : 0;
		}
		else if (pixel->bold)
		{
			wattron(window, A_BOLD);
			pixel->counter--;
			(pixel->counter <= 0) ? (pixel->bold = 0) : 0;
		}
	}
	else if (flag == OFF)
	{
		wattroff(window, A_BOLD);
		wattroff(window, COLOR_PAIR(pixel->color));
		wattroff(window, COLOR_PAIR(pixel->color + LIVE_COLOR));
	}
}

void			draw_map(t_win *win, t_vm *vm, unsigned char cols)
{
	char			*base;
	unsigned short	i;

	i = 0;
	base = "0123456789abcdef";
	CURSOR_Y = Y_BEGIN;
	CURSOR_X = X_BEGIN;
	while (i < MEM_SIZE)
	{
		attributes_action(win->window, g_pixels[i], ON);
		mvwaddch(win->window, win->cursor_y, win->cursor_x++, base[g_map[i] / 16]);
		mvwaddch(win->window, win->cursor_y, win->cursor_x++, base[g_map[i] % 16]);
		attributes_action(win->window, g_pixels[i], OFF);
		i++;
		if ((i % cols) == 0)
		{
			win->cursor_y++;
			win->cursor_x = X_BEGIN;
		}
		else
			mvwaddch(win->window, win->cursor_y, win->cursor_x++, ' ');
	}
	show_processes(win, vm, cols, base);
}

void	show_status(t_win *win)
{
	wattron(win->window, COLOR_PAIR((win->paused) ? 8 : 9) | A_BOLD);
	mvwprintw(win->window, Y_BEGIN, win->sidebar_pad + X_BEGIN, "** %s ** ", ((win->paused) ? "PAUSED" : "RUNNING"));
	wattroff(win->window, COLOR_PAIR((win->paused) ? 8 : 9));
}

void	sidebar_header(t_win *win, t_vm *vm)
{
	show_status(win);
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

int		ft_round(double n)
{
	int res;

	res = (int)n;
	n -= (double)res;
	if (n >= 0.5)
		return (res + 1);
	else
		return (res);
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
		tmp = ft_round(cost_live * bot->lives_cur_period);
		wattron(win->window, COLOR_PAIR(bot->player_counter));
		while (tmp > 0 && len < 50)
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

void	sidebar_footer(t_win *win, t_vm *vm)
{
	mvwprintw(win->window, CURSOR_Y, CURSOR_X, "CYCLE_TO_DIE : %d", vm->cycle_to_die);
	CURSOR_Y += 2;
	mvwprintw(win->window, CURSOR_Y, CURSOR_X, "CYCLE_DELTA : %d", CYCLE_DELTA);
	CURSOR_Y += 2;
	mvwprintw(win->window, CURSOR_Y, CURSOR_X, "NBR_LIVE : %d", NBR_LIVE);
	CURSOR_Y += 2;
	mvwprintw(win->window, CURSOR_Y, CURSOR_X, "MAX_CHECKS : %d", MAX_CHECKS);
	CURSOR_Y += 2;
}

void	show_sidebar(t_win *win, t_vm *vm)
{
	win->cursor_y = Y_BEGIN;
	win->cursor_x = win->sidebar_pad + X_BEGIN;
	wattron(win->window, COLOR_PAIR(7) | A_BOLD);
	sidebar_header(win, vm);
	sidebar_players(win, vm);
	sidebar_statistics(win, vm);
	sidebar_footer(win, vm);
	wattroff(win->window, COLOR_PAIR(7) | A_BOLD);
}

void	prepare_window(t_win *win, t_vm *vm)
{
	win->cursor_x = X_BEGIN;
	win->cursor_y = Y_BEGIN;
	clear();
	draw_table(win);
	draw_map(win, vm, 64);
	show_sidebar(win, vm);
	refresh();
	wrefresh(win->window);
}

void	compute_speed(t_win *win, int key)
{
	if (key == KEY_Q || key == KEY_W) /* q / w */
	{
		if (key == KEY_Q && win->speed > 10)
			win->speed -= 10;
		else if (key == KEY_W && win->speed > 1)
			win->speed -= 1;
		else
			win->speed = 1;
	}
	else if (key == KEY_E || key == KEY_R) /* e / r */
	{
		if (key == KEY_R && win->speed < 990)
			win->speed += 10;
		else if (key == KEY_E && win->speed < 1000)
			win->speed += 1;
		else
			win->speed = 1000;
	}
	wattron(win->window, COLOR_PAIR(7) | A_BOLD);
	mvwprintw(win->window, CURSOR_Y + 2, CURSOR_X + win->sidebar_pad + 22, "%-4d", win->speed);
	wattroff(win->window, COLOR_PAIR(7) | A_BOLD);
}

void	dispatcher_keys(t_win *win, t_vm *vm, int key, char *flag)
{
	if (key == RESIZE)	/* RESIZE */
		prepare_window(win, vm);
	else if (key == KEY_SPACE)	/* SPACE */
	{
		if (!*flag)
		{
			*flag = 1;
			nodelay(stdscr, true);
			win->paused = 0;
		}
		else
		{
			*flag = 0;
			nodelay(stdscr, false);
			win->paused = 1;
		}
		show_status(win);
	}
	else if (key == KEY_Q || key == KEY_W || key == KEY_E || key == KEY_R)
		compute_speed(win, key);
}

void		print_winner(t_win *win, t_vm *vm)
{
	mvwprintw(win->window, CURSOR_Y, CURSOR_X, "The winner is : %s", vm->winner->name);
	CURSOR_Y += 2;
	mvwprintw(win->window, CURSOR_Y, CURSOR_X, "Press any key to finish");
}

void	redraw(t_win *win, t_vm *vm, int key)
{
	static char	flag = 0;

	win->cursor_x = X_BEGIN;
	win->cursor_y = Y_BEGIN;
	if (key != -1)
		dispatcher_keys(win, vm, key, &flag);
	if (flag || key == KEY_S)
	{
		// step(vm);
		draw_map(win, vm, 64);
		show_sidebar(win, vm);
	}
	if (vm->winner)
		print_winner(win, vm);
	wrefresh(win->window);
}

void		fill_pixel_map(t_bot *bot, char count_players)
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
			g_pixels[total + i]->empty = 0;
			i++;
		}
		total += MEM_SIZE / count_players;
		bot_counter++;
		bot = bot->next;
	}
}

void	create_pixel_map(t_vm *vm)
{
	g_pixels = (t_pixel **)malloc(sizeof(t_pixel *) * MEM_SIZE);
	(!g_pixels) ? ft_error("Error") : ft_bzero_pixel_map();
	fill_pixel_map(vm->bot, vm->count_players);
}

void	visualize(t_vm *vm)
{
	t_win	*win;
	int		key;

	key = 0;
	create_pixel_map(vm);
	initscr();
	noecho();
	preparation();
	win = init_win();
	prepare_window(win, vm);
	while ((key = getch()) && !vm->winner)
		redraw(win, vm, key);
	delwin(win->window);
	endwin();
}
