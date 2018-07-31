/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 14:03:16 by tkiselev          #+#    #+#             */
/*   Updated: 2018/07/19 14:03:20 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				check_magic_header(int fd)
{
	unsigned int	magic_header;

	if (read(fd, &magic_header, 4) != 4)
		ft_error("Error");
	magic_header = reverse_bytes(magic_header, 4);
	if (magic_header != COREWAR_EXEC_MAGIC)
		ft_error("Error");
}

static void			check_arguments(char opcode, char *types, t_bot *bot, unsigned int *i)
{
	unsigned char	count;

	count = 0;
	while (types[count])
	{
		if (types[count] == REG_CODE)
		{
			if (*i >= bot->size || bot->exec[*i] > REG_NUMBER)
				ft_error("Error");
			*i += T_REG_SIZE;
		}
		else if (types[count] == IND_CODE)
		{
			if ((*i + 1) >= bot->size)
				ft_error("Error");
			*i += T_DIR_SIZE;
		}
		else if (types[count] == DIR_CODE)
		{
			if ((*i + LABEL_SIZE(opcode) - 1) >= bot->size)
				ft_error("Error");
			*i += LABEL_SIZE(opcode);
		}
		count++;
	}
}

static void			check_command(t_bot *new, unsigned int *i)
{
	char			opcode;
	char			codage[4];

	opcode = new->exec[*i];
	(*i)++;
	if (CODAGE(opcode))
	{
		(new->exec[*i] == '\0') ? ft_error("Error") : 0;
		decipher_codage(codage, COUNT_ARGS(opcode), new->exec[*i]);
		(*i)++;
	}
	else
		pseudo_codage(codage, opcode);
	check_arguments(opcode, codage, new, i);
}

/*
** This function checks executable of a bot.
**
** Specifically this function checks whether i points on opcode or not.
** i - it is a counter for the whole executable 
** which will skip in function check_command
** command + codage + arguments.
*/

void				check_executable(t_bot *bot)
{
	unsigned int	i;

	i = 0;
	while (i < bot->size)
	{
		if (bot->exec[i] > 0 && bot->exec[i] <= MAX_TABLE)
			check_command(bot, &i);
		else
			ft_error("Error");
	}
}
