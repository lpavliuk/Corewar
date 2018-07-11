/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_symbol_s_uni.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <opavliuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 20:46:54 by opavliuk          #+#    #+#             */
/*   Updated: 2018/05/14 13:44:12 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_unicode(t_str *pf, wchar_t *str_uni)
{
	int n;
	int c;

	c = 0;
	n = 0;
	N_UNI = 0;
	while (str_uni[N_UNI] != '\0')
	{
		if (str_uni[N_UNI] > 127 && str_uni[N_UNI] <= 2047)
			n += 2;
		else if (str_uni[N_UNI] > 2047 && str_uni[N_UNI] <= 65535)
			n += 3;
		else if (str_uni[N_UNI] > 65535 && str_uni[N_UNI] <= 1114111)
			n += 4;
		else
			n++;
		if (PREC && n > PREC)
			return (c);
		c = n;
		N_UNI++;
	}
	return (n);
}

static void	write_unicode_to_buffer(t_str *pf, wchar_t *str_uni, int len)
{
	int i;

	i = 0;
	while (str_uni[i] != '\0' && i < len)
	{
		write_to_buffer(pf, str_uni[i]);
		i++;
	}
}

void		write_symbol_s_uni(t_str *pf, wchar_t *str_uni, int n)
{
	if ((!DOT && !PREC) || PREC)
		PREC = count_unicode(pf, str_uni);
	if (WIDTH < 0)
	{
		if (DOT && n >= PREC)
			write_unicode_to_buffer(pf, str_uni, N_UNI);
		else
			write_unicode_to_buffer(pf, str_uni, N_UNI);
		while (WIDTH++ < (PREC * -1))
			write_to_buffer(pf, ' ');
	}
	else
	{
		while (WIDTH-- > PREC)
		{
			if (ZERO && !MINUS)
				write_to_buffer(pf, '0');
			else
				write_to_buffer(pf, ' ');
		}
		if (DOT && n >= PREC)
			write_unicode_to_buffer(pf, str_uni, N_UNI);
		else
			write_unicode_to_buffer(pf, str_uni, N_UNI);
	}
}
