/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 10:41:23 by opavliuk          #+#    #+#             */
/*   Updated: 2018/03/28 20:24:16 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_letters(char *g, int i, char c)
{
	int l;

	l = 0;
	while (g[i] != '\0' && g[i] != c)
	{
		i++;
		l++;
	}
	return (l);
}

static void		ft_wordscpy(char *d, char *g, size_t i, size_t l)
{
	size_t n;

	n = 0;
	while (n < l)
	{
		d[n] = g[i];
		i++;
		n++;
	}
	d[n] = '\0';
}

static char		**ft_split(char **d, char *g, char c, size_t i)
{
	size_t k;
	size_t l;

	k = 0;
	l = 0;
	while (g[i] != '\0')
	{
		while (g[i] == c && g[i] != '\0')
			i++;
		if (g[i] == '\0')
			break ;
		l = (count_letters(g, i, c));
		d[k] = (char *)malloc(sizeof(char) * (l + 1));
		if (d[k] == NULL)
		{
			ft_stralldel(d, k);
			return (NULL);
		}
		ft_bzero(d[k], (l + 1));
		ft_wordscpy(d[k], g, i, l);
		i = i + l;
		k++;
	}
	d[k] = 0;
	return (d);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	i;
	size_t	n;
	char	*g;
	char	**d;

	i = 0;
	n = 0;
	g = (char *)s;
	if (s == NULL)
		return (NULL);
	n = ft_count_words(g, c);
	d = (char **)malloc(sizeof(char *) * (n + 1));
	if (d == NULL)
		return (NULL);
	d = ft_split(d, g, c, i);
	return (d);
}
