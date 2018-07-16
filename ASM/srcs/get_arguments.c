/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 16:39:55 by tkiselev          #+#    #+#             */
/*   Updated: 2018/07/16 16:39:57 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

/*
** We pass flag just in order to determine if this argument is INT or CHAR *.
** 'add_argument(command, type, get_data(type, arr[i], &flag), flag)'
*/

static	void	foreach_arg(char **arr, t_command *command)
{
	int			i;
	char		type;
	char		flag;

	i = 0;
	while (arr[i])
	{
		flag = 0;
		type = get_type(arr[i]);
		if (type == UNDEFINED_TYPE)
			ft_error("Error");
		add_argument(command, type, get_data(type, arr[i], &flag), flag);
		i++;
	}
}

static	void	check_arguments(t_command *command)
{
	t_arg		*arg;
	int			len;

	len = 0;
	arg = command->args;
	while (arg)
	{
		(len > 3) ? ft_error("Error") : 0;
		(!ARG(command->opcode, len, arg->type)) ? ft_error("Error") : 0;
		len++;
		arg = arg->next;
	}
	(COUNT_ARGS(command->opcode) != len) ? ft_error("Error") : 0;
}

static	void	skip_args(char *s, char **arr, int *j)
{
	int			i;

	i = 0;
	while (arr[i])
	{
		*j = ft_strstr(s + *j, arr[i]) - s + ft_strlen(arr[i]);
		i++;
	}
}

static	void	array_map(char **arr, void (*f)(char **))
{
	int			i;

	i = 0;
	while (arr[i])
	{
		(*f)(&arr[i]);
		i++;
	}
}

void			get_arguments(t_asm *asmb, t_command *new, int *j)
{
	char		**arr;

	if (!(arr = ft_strsplit(asmb->line + *j, SEPARATOR_CHAR)))
		ft_error("Error");
	array_map(arr, ft_strtrim);
	foreach_arg(arr, new);
	skip_args(asmb->line, arr, j);
	array_map(arr, ft_strdel);
	free(arr);
	check_arguments(new);
}
