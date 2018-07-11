/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_type_d_i.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <opavliuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 12:21:22 by opavliuk          #+#    #+#             */
/*   Updated: 2018/05/14 13:44:39 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	check_flags(intmax_t *i, short int n, t_str *pf)
{
	if (PLUS && *i >= 0)
		BUFFER[N++] = '+';
	else if (SPACE && !PLUS && *i >= 0 && WIDTH == PREC)
		BUFFER[N++] = ' ';
	else if (((PREC || ZERO) && WIDTH > n) && *i < 0)
	{
		BUFFER[N++] = '-';
		if (PLUS)
			WIDTH++;
		else if (WIDTH == PREC && ++WIDTH)
			PREC++;
		(*i) *= -1;
	}
	if ((PLUS && (*i) >= 0 && WIDTH) || (SPACE && WIDTH != PREC))
	{
		if (WIDTH < 0)
			WIDTH++;
		else if ((DOT && (*i) == 0) || (SPACE && *i == 0 && !PLUS))
			return ;
		else
			WIDTH--;
	}
}

static void	working_while(intmax_t *i, short int n, t_str *pf)
{
	if (*i < 0 && PREC > n && WIDTH > n)
		WIDTH--;
	while (WIDTH > n)
	{
		if (WIDTH == PREC)
		{
			if (PLUS || (SPACE && !ZERO && WIDTH == PREC))
				--N;
			check_flags(&(*i), n, pf);
		}
		if (WIDTH <= PREC || (ZERO && !MINUS))
			write_to_buffer(pf, '0');
		else
			write_to_buffer(pf, ' ');
		WIDTH--;
	}
}

static void	write_to_buffer_digital(intmax_t i, short int n, t_str *pf)
{
	if (DOT && i == 0)
		n = 0;
	if (((PLUS && WIDTH && !ZERO && !DOT)
		|| (SPACE && WIDTH && !PLUS && !DOT)) && !MINUS && i == 0)
		WIDTH--;
	if (WIDTH < 0)
	{
		check_flags(&i, n, pf);
		while (PREC-- > n && WIDTH++)
			write_to_buffer(pf, '0');
		ft_putnbr_base(i, 10, 0, pf);
		while (WIDTH++ < (n * (-1)))
			write_to_buffer(pf, ' ');
	}
	else
	{
		if (WIDTH < n || ZERO || WIDTH == PREC)
			check_flags(&i, n, pf);
		working_while(&i, n, pf);
		if (WIDTH && WIDTH == n && !ZERO)
			check_flags(&i, n, pf);
		if (DOT && i == 0)
			return ;
		ft_putnbr_base(i, 10, 0, pf);
	}
}

int			write_type_d_i(va_list ap, t_str *pf)
{
	short int	n;
	intmax_t	i;

	if ((MODF[0] == 'l' && MODF[1] == '\0') || TYPE == 'D')
		i = va_arg(ap, long int);
	else if (MODF[0] == 'l' && MODF[1] == 'l')
		i = va_arg(ap, long long int);
	else if (MODF[0] == 'h' && MODF[1] == '\0')
		i = (short int)va_arg(ap, int);
	else if (MODF[0] == 'h' && MODF[1] == 'h')
		i = (signed char)va_arg(ap, int);
	else if (MODF[0] == 'z' && MODF[1] == '\0')
		i = va_arg(ap, size_t);
	else if (MODF[0] == 'j' && MODF[1] == '\0')
		i = va_arg(ap, intmax_t);
	else
		i = va_arg(ap, int);
	n = ft_count(i, 10);
	if ((DOT || PREC) && PREC >= 0 && i >= 0)
		ZERO = 0;
	if (PREC > WIDTH && WIDTH >= 0)
		WIDTH = PREC;
	write_to_buffer_digital(i, n, pf);
	return (0);
}
