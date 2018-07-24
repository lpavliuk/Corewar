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

typedef struct
{
	WINDOW	*window;
	int		height;
	int		width;
	int		sidebar_pad; /* Sidebar padding - quantity of columns to sidebar */
	int		cursor_y;
	int		cursor_x;
}			t_win;

#endif
