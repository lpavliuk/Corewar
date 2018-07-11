/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 20:48:32 by opavliuk          #+#    #+#             */
/*   Updated: 2018/03/27 15:30:49 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_copy(char *d, char const *s, size_t i, size_t n)
{
	size_t k;

	k = 0;
	while (k <= n)
	{
		d[k] = s[i];
		k++;
		i++;
	}
	d[k] = '\0';
	return (d);
}

char		*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	n;
	size_t	k;
	char	*d;

	i = 0;
	n = 0;
	k = -1;
	if (s == NULL)
		return (NULL);
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && s[n] != '\0')
		s++;
	if (s[i] != '\0')
		n = (ft_strlen(s) - 1);
	while ((s[n] == ' ' || s[n] == '\n' || s[n] == '\t') && s[n] != '\0')
		n--;
	d = (char *)malloc(sizeof(char) * (n + 2));
	if (d == NULL)
		return (NULL);
	ft_bzero(d, (n + 2));
	d = ft_copy(d, s, i, n);
	return (d);
}
