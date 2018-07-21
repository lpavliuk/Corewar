/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 17:36:20 by tkiselev          #+#    #+#             */
/*   Updated: 2018/07/21 17:36:21 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"

int	output_chars(unsigned char *s, char len)
{
	char	i;

	i = 0;
	while (i < len)
	{
		if (s[i] > 32 && s[i] < 127)
			write(1, &s[i], 1);
		else
			write(1, ".", 1);
		i++;
	}
	write(1, "\n", 1);
	return (1);
}

void	print(unsigned char *tab, size_t size)
{
	size_t	spaces;
	size_t	i;
	size_t	total;

	i = 0;
	spaces = 0;
	total = 0;
	while (i < size)
	{
		(spaces == 0) ? (spaces = 40) : 0;
		ft_printf("%02x", tab[i]) && (spaces -= 2) && (i++);
		if (i % 2 == 0)
			write(1, " ", 1) && (spaces--);
		if (i % 16 == 0)
			output_chars(tab + total, 16) && (total += 16);
	}
	i %= 16;
	if (i != 0)
	{
		while (spaces-- > 0)
			write(1, " ", 1);
		output_chars(tab + total, i);
	}
}

void	print_memory(const void *addr, size_t size)
{
	unsigned char	*tab;

	if (!addr || size == 0)
		return ;
	tab = (unsigned char *)addr;
	print(tab, size);
}

int	main(void)
{
	int	tab[10] = {0, 23, 150, 255,
	              12, 16,  21, 42};

	print_memory(tab, sizeof(tab));
	return (0);
}