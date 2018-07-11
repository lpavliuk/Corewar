/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_type_x_p.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <opavliuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 12:38:46 by opavliuk          #+#    #+#             */
/*   Updated: 2018/05/14 13:45:08 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	check_hash(t_str *pf)
{
	BUFFER[N++] = '0';
	if (TYPE == 'x' || TYPE == 'p')
		BUFFER[N++] = 'x';
	else
		BUFFER[N++] = 'X';
}

static int	write_width(uintmax_t un_i, t_str *pf, short int n)
{
	while (WIDTH-- > n)
	{
		if (WIDTH == PREC && HASH && un_i != 0)
			check_hash(pf);
		else if (WIDTH < PREC || (ZERO && !MINUS))
			write_to_buffer(pf, '0');
		else
			write_to_buffer(pf, ' ');
	}
	if ((TYPE == 'p' && !ZERO) || (PREC < n && !ZERO && HASH && un_i != 0))
		check_hash(pf);
	if (TYPE == 'x' && DOT && PREC == 0 && WIDTH >= 0)
		write_to_buffer(pf, ' ');
	else if ((TYPE == 'x' || TYPE == 'p') && DOT && PREC == 0 && un_i == 0)
		return (1);
	else
	{
		if (TYPE == 'x' || TYPE == 'p')
			ft_unputnbr_base(un_i, 16, 0, pf);
		else if (DOT && PREC == 0 && un_i == 0)
			return (0);
		else
			ft_unputnbr_base(un_i, 16, 1, pf);
	}
	return (0);
}

static void	write_to_buffer_un_digital(uintmax_t un_i, short int n, t_str *pf)
{
	if (WIDTH < 0)
	{
		if ((HASH && un_i != 0) || TYPE == 'p')
			check_hash(pf);
		if (TYPE == 'x' || TYPE == 'p')
			ft_unputnbr_base(un_i, 16, 0, pf);
		else
			ft_unputnbr_base(un_i, 16, 1, pf);
		while (WIDTH++ < (n * (-1)))
			write_to_buffer(pf, ' ');
	}
	else
	{
		if ((TYPE == 'p' && ZERO) || (((PREC >= n && WIDTH <= PREC)
			|| ZERO) && HASH && un_i != 0))
			check_hash(pf);
		if (write_width(un_i, pf, n))
			return ;
	}
}

int			write_type_x_p(va_list ap, t_str *pf)
{
	short int	n;
	uintmax_t	un_i;

	if (TYPE == 'p')
		un_i = va_arg(ap, uintmax_t);
	else
		un_i = check_modifier_un_int(ap, pf);
	n = ft_count(un_i, 16);
	if (TYPE == 'p' || (HASH && un_i != 0))
		n += 2;
	else if (PREC && WIDTH < PREC && un_i != 0)
		n++;
	if (DOT || PREC)
		ZERO = 0;
	if (PREC && PREC > WIDTH)
	{
		ZERO++;
		if (un_i != 0 || TYPE == 'p')
			n -= 2;
		if ((TYPE == 'x' || TYPE == 'X') && !HASH && un_i != 0)
			n++;
		WIDTH = PREC;
	}
	write_to_buffer_un_digital(un_i, n, pf);
	return (0);
}
