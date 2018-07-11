/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 13:56:55 by opavliuk          #+#    #+#             */
/*   Updated: 2018/04/13 22:16:43 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*d;
	size_t	i;

	i = 0;
	while (s1[i] != '\0')
		i++;
	d = (char *)malloc(sizeof(char) * (i + 1));
	if (d == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		d[i] = s1[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}
