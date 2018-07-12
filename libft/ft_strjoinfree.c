/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 13:01:02 by tkiselev          #+#    #+#             */
/*   Updated: 2018/07/12 14:35:00 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(const char *s1, const char *s2, char n)
{
	char	*s;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 || !s2)
		return ((!s1) ? (char*)s2 : (char*)s1);
	if (!(s = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	i = -1;
	while ((char)s1[++i] != '\0')
		s[i] = (char)s1[i];
	j = -1;
	while ((char)s2[++j] != '\0')
		s[i++] = (char)s2[j];
	if (n == 1 || n == 2)
		free((n == 1) ? (char*)s1 : (char*)s2);
	else if (n == 3)
	{
		free((char*)s1);
		free((char*)s2);
	}
	return (s);
}
