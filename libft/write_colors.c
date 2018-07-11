/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <opavliuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 20:49:43 by opavliuk          #+#    #+#             */
/*   Updated: 2018/05/14 13:44:03 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_colors(char *colors, t_str *pf)
{
	if (!ft_strcmp(colors, "eoc"))
		ft_cpy_to_buffer(pf, (unsigned char *)EOC, 5);
	else if (!ft_strcmp(colors, "red"))
		ft_cpy_to_buffer(pf, (unsigned char *)RED, 5);
	else if (!ft_strcmp(colors, "green"))
		ft_cpy_to_buffer(pf, (unsigned char *)GREEN, 5);
	else if (!ft_strcmp(colors, "yellow"))
		ft_cpy_to_buffer(pf, (unsigned char *)YELLOW, 5);
	else if (!ft_strcmp(colors, "blue"))
		ft_cpy_to_buffer(pf, (unsigned char *)BLUE, 5);
	else if (!ft_strcmp(colors, "pink"))
		ft_cpy_to_buffer(pf, (unsigned char *)PINK, 5);
	else if (!ft_strcmp(colors, "white"))
		ft_cpy_to_buffer(pf, (unsigned char *)WHITE, 5);
	else
		return (0);
	return (1);
}

int			write_colors(const char *format, t_str *pf)
{
	short int	n;
	char		colors[7];

	n = 0;
	format++;
	ft_bzero(colors, 7);
	while (format[n] != '\0' && n < 7)
	{
		if (format[n] == '}')
		{
			if (check_colors(colors, pf))
				return (n + 2);
			break ;
		}
		colors[n] = format[n];
		n++;
	}
	return (0);
}
