/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_percent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <opavliuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 19:48:08 by opavliuk          #+#    #+#             */
/*   Updated: 2018/05/14 13:46:23 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	separator(char c)
{
	if (c != 's' && c != 'S' && c != 'p' && c != 'd'
		&& c != 'D' && c != 'i' && c != 'o' &&
		c != 'O' && c != 'u' && c != 'U' &&
		c != 'x' && c != 'X' && c != 'c' && c != 'C')
		return (1);
	else
		return (0);
}

static void	check_flags(const char *format, int *i, t_str *pf)
{
	while ((format[*i] == '0' || !ft_isdigit(format[*i])))
	{
		if (format[*i] == '+' || format[*i] == '-')
		{
			if (format[*i] == '-')
				MINUS++;
			else
				PLUS++;
		}
		else if (format[*i] == '#')
			HASH++;
		else if (format[*i] == '0')
			ZERO++;
		else if (format[*i] == ' ')
			SPACE++;
		else if (format[*i] == '.' && format[*i + 1] == ' ')
			DOT = 1;
		else
			return ;
		(*i)++;
	}
}

static void	check_star(va_list ap, const char *format, t_str *pf, int *i)
{
	int n;

	n = *i;
	if (format[*i] == '*' && ++(*i))
	{
		WIDTH = va_arg(ap, int);
		while (format[n] != '.' && !ft_isalpha(format[n]))
		{
			if (format[n] == '0' && !ZERO)
				ZERO++;
			n++;
		}
	}
	else if (format[*i] == '.' && format[*i + 1] == '*' && ++(*i) && ++DOT)
	{
		PREC = va_arg(ap, int);
		if (PREC >= 0)
			(*i)++;
	}
	else if (format[*i] == '.' && ++(*i))
		PREC = ft_atoi(format + (*i)--);
	else
		WIDTH = ft_atoi(format + *i);
	if (PREC < 0 && ++(*i) && (DOT * 0))
		PREC = 0;
}

static int	check_another(va_list ap, const char *format, int *i, t_str *pf)
{
	while (separator(format[*i]) && format && format[*i] != '\0')
	{
		if ((format[*i] == '.' && ++DOT) || format[*i] == '*')
			check_star(ap, format, pf, &(*i));
		else if (format[*i] == 'h' || format[*i] == 'l'
			|| format[*i] == 'j' || format[*i] == 'z')
		{
			MODF[0] = format[*i];
			(*i)++;
			if ((format[*i] == 'l' && format[*i - 1] == 'l')
				|| (format[*i] == 'h' && format[*i - 1] == 'h'))
				MODF[1] = format[(*i)++];
			if (format[*i] == '\0')
				return (1);
			break ;
		}
		else if (!ft_isdigit(format[*i]) && format[*i] != ' ')
			break ;
		if (separator(format[*i]))
			(*i)++;
	}
	return (0);
}

int			check_percent(va_list ap, const char *format, t_str *pf)
{
	int	i;

	i = 1;
	check_flags(format, &i, pf);
	if (format[i] == '\0')
		return (i);
	check_star(ap, format, pf, &i);
	if (format[i] == '\0')
		return (i);
	if (ft_isdigit(format[i]) || format[i] == '*')
		check_star(ap, format, pf, &i);
	write_space_to_buffer(pf);
	if (check_another(ap, format, &i, pf))
		return (i);
	if (format[i] != '\0')
		TYPE = format[i];
	return ((i == 0) ? i : i + 1);
}
