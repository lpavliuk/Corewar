/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizator.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 19:58:18 by tkiselev          #+#    #+#             */
/*   Updated: 2018/07/23 19:58:20 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZE_H
# define VISUALIZE_H

# include "../corewar.h"
# include <curses.h>

# define X_BEGIN 3
# define Y_BEGIN 2

/*
** COLOR + foreground color + background color
*/

# define COLOR_LAYOUT COLOR_PAIR(6)

typedef struct
{
	WINDOW	*window;
	int		height;
	int		width;
	int		sidebar_pad; /* Sidebar padding - quantity of columns to sidebar */
	int		cursor_y;
	int		cursor_x;
}			t_win;

typedef struct	s_vm 	t_vm;
typedef struct	s_pixel t_pixel;

void					visualize(t_vm *vm);

#endif
