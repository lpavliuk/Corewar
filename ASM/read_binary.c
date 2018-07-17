/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 10:37:29 by opavliuk          #+#    #+#             */
/*   Updated: 2018/07/17 10:37:30 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/************** DELETE IT !!!! *******************/
t_asm		*init_asmb(void)
{
	t_asm	*s;

	if (!(s = (t_asm*)malloc(sizeof(t_asm))))
		ft_error("Error [init_asmb()]: memory was not allocated");
	ft_bzero(s->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(s->comment, COMMENT_LENGTH + 1);
	s->file_name = NULL;
	s->command = NULL;
	s->line = NULL;
	s->flag_a = 0;
	s->prog_size = 0;
	s->new_fd = 0;
	s->fd = 0;
	s->last_line_size = 0;
	s->magic = COREWAR_EXEC_MAGIC;
	return (s);
}
/************************************************/


int			main(void)
{
	t_asm		*asmb;

	asmb = init_asmb();
	return (0);
}
