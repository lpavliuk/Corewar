/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_type_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <opavliuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:12:06 by opavliuk          #+#    #+#             */
/*   Updated: 2018/05/14 13:44:33 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	write_symbol_c_uni(wchar_t c_uni, t_str *pf)
{
	int i;

	i = 2;
	if (c_uni > 2047 && c_uni <= 65535)
		i = 3;
	else if (c_uni > 65535 && c_uni <= 1114111)
		i = 4;
	if (WIDTH < 0)
	{
		i *= -1;
		write_to_buffer(pf, c_uni);
		while (WIDTH++ < i)
			write_to_buffer(pf, ' ');
	}
	else
	{
		while (WIDTH-- > i)
		{
			if (ZERO && !MINUS)
				write_to_buffer(pf, '0');
			else
				write_to_buffer(pf, ' ');
		}
		write_to_buffer(pf, c_uni);
	}
}

static void	write_symbol_c(char c, t_str *pf)
{
	if (WIDTH < 0)
	{
		if (c == 0)
			BUFFER[N++] = '\0';
		else
			write_to_buffer(pf, c);
		while (WIDTH++ < -1)
			write_to_buffer(pf, ' ');
	}
	else
	{
		while (WIDTH-- > 1)
		{
			if (ZERO && !MINUS)
				write_to_buffer(pf, '0');
			else
				write_to_buffer(pf, ' ');
		}
		if (c == 0)
			BUFFER[N++] = '\0';
		else
			write_to_buffer(pf, c);
	}
}

static void	check_zero(wchar_t c_uni, t_str *pf)
{
	if (c_uni == 0)
		BUFFER[N++] = '\0';
	else if ((c_uni >= 0 && c_uni <= 255) && MB_CUR_MAX == 1)
		write_symbol_c((int)c_uni, pf);
	else
		write_symbol_c_uni(c_uni, pf);
}

static int	work_with_width(wchar_t c_uni, char c, t_str *pf)
{
	if ((TYPE == 'C' || (TYPE == 'c' && MODF[0] == 'l')) && c_uni > 255)
		write_symbol_c_uni(c_uni, pf);
	else if ((TYPE == 'C' || (TYPE == 'c' && MODF[0] == 'l'))
		&& (c_uni >= 0 && c_uni <= 255) && MB_CUR_MAX == 4)
		write_symbol_c_uni(c_uni, pf);
	else if ((TYPE == 'C' || (TYPE == 'c' && MODF[0] == 'l'))
		&& (c_uni >= 0 && c_uni <= 255))
		write_symbol_c((int)c_uni, pf);
	else
		write_symbol_c(c, pf);
	return (0);
}

int			write_type_c(va_list ap, t_str *pf)
{
	char	c;
	wchar_t	c_uni;

	if (TYPE == 'C' || (TYPE == 'c' && MODF[0] == 'l'))
		c_uni = va_arg(ap, wchar_t);
	else if (TYPE != 'c')
		c = TYPE;
	else
		c = va_arg(ap, int);
	if ((TYPE == 'C' || (TYPE == 'c' && MODF[0] == 'l'))
		&& ((c_uni > 255 && MB_CUR_MAX == 1) || c_uni < 0))
		return (1);
	else if (WIDTH != 0)
		work_with_width(c_uni, c, pf);
	else
	{
		if (TYPE == 'C' || (TYPE == 'c' && MODF[0] == 'l'))
			check_zero(c_uni, pf);
		else
			write_to_buffer(pf, c);
	}
	return (0);
}
