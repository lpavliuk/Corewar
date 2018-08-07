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
** line 32: '3' - is a CTRL + C
*/

void	visualize(void)
{
	t_win	*win;
	int		key;

	create_pixel_map();
	fill_pixel_map();
	initscr();
	noecho();
	raw();
	color_preparation();
	win = init_win();
	prepare_window(win);
	while ((key = getch()) != 3 && !g_vm->winner)
		redraw(win, key);
	delwin(win->window);
	endwin();
	free(win);
}
