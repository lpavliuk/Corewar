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

	s = (t_asm*)malloc(sizeof(t_asm));
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

static void		read_info(t_asm *asmb)
{
	char	null[4];

	read(asmb->fd, &asmb->magic, 4);
	asmb->magic = reverse_bytes(asmb->magic, 4);
	if (asmb->magic != COREWAR_EXEC_MAGIC)
		ft_error("Incorrect magic-header in file!");
	read(asmb->fd, asmb->prog_name, PROG_NAME_LENGTH);
	read(asmb->fd, null, 4);
	read(asmb->fd, &asmb->prog_size, 4);
	asmb->prog_size = reverse_bytes(asmb->prog_size, 4);
	read(asmb->fd, asmb->comment, COMMENT_LENGTH);
}

static void		read_executable(t_asm *asmb)
{

}

int				main(void)
{
	unsigned char	buffer[5];
	t_asm			*asmb;

	/*********** DELETE IT ****************/
	asmb = init_asmb();
	asmb->fd = open("toto.cor", O_RDONLY);
	/**************************************/

	ft_bzero(buffer, 5);
	read_info(asmb);
	read_executable(asmb);

	ft_printf("name: %s\n", asmb->prog_name);
	ft_printf("size: %d\n", asmb->prog_size);
	ft_printf("comment: %s\n", asmb->comment);
	return (0);
}
