/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 19:15:47 by opavliuk          #+#    #+#             */
/*   Updated: 2018/03/28 20:22:50 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*d;

	i = 0;
	if (s == NULL)
		return (NULL);
	d = (char *)malloc(sizeof(char) * (len + 1));
	if (d == NULL)
		return (NULL);
	ft_bzero(d, (len + 1));
	while (s[i] != '\0' && len > 0)
	{
		d[i] = s[start];
		i++;
		start++;
		len--;
	}
	d[i] = '\0';
	return (d);
}
