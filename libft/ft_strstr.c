/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 13:33:24 by opavliuk          #+#    #+#             */
/*   Updated: 2018/03/28 20:16:09 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	check_str(char *b, char *l, size_t i, size_t n)
{
	while (b[i] == l[n])
	{
		if (b[i + 1] == '\0' && l[n + 1] == '\0')
			return (0);
		i++;
		n++;
	}
	if (l[n] == '\0')
		return (0);
	else
		return (1);
}

char			*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	n;
	char	*b;
	char	*l;

	i = 0;
	b = (char *)big;
	l = (char *)little;
	if (l[i] == '\0')
		return (b);
	while (b[i] != '\0')
	{
		n = 0;
		if (b[i] == l[n])
		{
			n = check_str(b, l, i, n);
			if (!n)
				return (b + i);
		}
		i++;
	}
	return (NULL);
}
