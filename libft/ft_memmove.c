/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 18:13:10 by opavliuk          #+#    #+#             */
/*   Updated: 2018/03/28 19:46:06 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (dst > src)
		while (len > 0)
		{
			d[len - 1] = s[len - 1];
			len--;
		}
	else if (d <= s)
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	return (d);
}
