/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 21:52:46 by opavliuk          #+#    #+#             */
/*   Updated: 2018/03/26 21:28:50 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t n;
	size_t c;

	i = 0;
	n = 0;
	i = ft_strlen(dst);
	if (i < size)
		c = i + ft_strlen(src);
	else
		c = size + ft_strlen(src);
	while (i < (size - 1) && src != '\0' && size)
	{
		dst[i] = src[n];
		i++;
		n++;
	}
	dst[i] = '\0';
	return (c);
}
