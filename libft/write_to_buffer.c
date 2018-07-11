/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <opavliuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 16:00:43 by opavliuk          #+#    #+#             */
/*   Updated: 2018/05/14 13:44:23 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_cpy_to_buffer(t_str *pf, unsigned char *code, int len)
{
	int i;

	i = 0;
	if (TYPE == 'c' && code[0] == 0)
		BUFFER[N++] = 0;
	while (code[i] != '\0' && i < len)
	{
		if (N > 41)
			check_buffer(pf, 0, 0);
		BUFFER[N] = code[i];
		i++;
		N++;
	}
}

void		write_to_buffer(t_str *pf, int c)
{
	unsigned char	code[5];

	ft_bzero(code, 5);
	if (c <= 127)
		code[0] = (char)c;
	else if (c <= 2047)
	{
		code[0] = 192 | ((c >> 6) & 31);
		code[1] = 128 | (c & 63);
	}
	else if (c <= 65535)
	{
		code[0] = 224 | ((c >> 12) & 15);
		code[1] = 128 | ((c >> 6) & 63);
		code[2] = 128 | (c & 63);
	}
	else if (c <= 1114111)
	{
		code[0] = 240 | ((c >> 18) & 7);
		code[1] = 128 | ((c >> 12) & 63);
		code[2] = 128 | ((c >> 6) & 63);
		code[3] = 128 | (c & 63);
	}
	ft_cpy_to_buffer(pf, code, 5);
}

void		write_space_to_buffer(t_str *pf)
{
	int n;
	int x;

	if (WIDTH)
	{
		n = N;
		x = WIDTH;
		if (x < 0)
			x *= -1;
		while (x-- >= 1)
		{
			if (ZERO && !MINUS)
				write_to_buffer(pf, '0');
			else
				write_to_buffer(pf, ' ');
		}
		N = n;
		if (MINUS && WIDTH > 0)
			WIDTH *= -1;
	}
}
