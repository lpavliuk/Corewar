/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 17:43:56 by opavliuk          #+#    #+#             */
/*   Updated: 2018/03/28 20:22:12 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	if (s1[i] == s2[i])
	{
		while (s1[i] == s2[i] && s1[i] != '\0'
				&& s2[i] != '\0')
			i++;
		if (s1[i] != s2[i])
			return (0);
		else
			return (1);
	}
	return (0);
}
