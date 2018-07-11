/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 18:06:15 by opavliuk          #+#    #+#             */
/*   Updated: 2018/03/28 20:22:32 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	if (n == 0)
		return (1);
	if (s1[i] == s2[i] && n > 0)
	{
		while (s1[i] == s2[i] && s1[i] != '\0'
				&& s2[i] != '\0' && n > 0)
		{
			n--;
			if (n == 0)
				break ;
			i++;
		}
		if (s1[i] != s2[i])
			return (0);
		else
			return (1);
	}
	return (0);
}
