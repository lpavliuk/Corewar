/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 13:25:20 by opavliuk          #+#    #+#             */
/*   Updated: 2018/03/28 19:48:49 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*d;

	i = 0;
	d = (char *)s;
	while (d[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (d[i] == (char)c)
			return (d + i);
		i--;
	}
	return (NULL);
}
