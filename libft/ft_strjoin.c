/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 19:55:19 by opavliuk          #+#    #+#             */
/*   Updated: 2018/04/13 22:20:00 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	size_t		n;
	char		*d;

	i = 0;
	n = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	d = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (d == NULL)
		return (NULL);
	ft_bzero(d, (ft_strlen(s1) + ft_strlen(s2) + 1));
	while (s1[i] != '\0')
	{
		d[i] = s1[i];
		i++;
	}
	while (s2[n] != '\0')
	{
		d[i] = s2[n];
		i++;
		n++;
	}
	d[i] = '\0';
	return (d);
}
