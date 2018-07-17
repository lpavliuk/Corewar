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

static t_command	*initial_command(t_asm *asmb)
{
	if (!asmb->command)
	{
		asmb->command = malloc(sizeof(t_command));
		asmb->command->name = 0;
		asmb->command->opcode = 0;
		asmb->command->bytes = 0;
		asmb->command->bb = 0;
		asmb->command->codage = 0;
		asmb->command->labels = NULL;
		asmb->command->args = NULL;
		asmb->command->next = NULL;
		return (asmb->command);	
	}
	while (asmb->command->next)
		asmb->command = asmb->command->next;
	asmb->command->next = malloc(sizeof(t_command));
	asmb->command->next->name = 0;
	asmb->command->next->opcode = 0;
	asmb->command->next->bytes = 0;
	asmb->command->next->bb = 0;
	asmb->command->next->codage = 0;
	asmb->command->next->labels = NULL;
	asmb->command->next->args = NULL;
	asmb->command->next->next = NULL;
	return (asmb->command->next);
}

static void		read_info(t_asm *asmb)
{
	char	null[4];

	if (read(asmb->fd, &asmb->magic, 4) == 0)
		ft_error("Not enough data in file!");
	asmb->magic = reverse_bytes(asmb->magic, 4);
	if (asmb->magic != COREWAR_EXEC_MAGIC)
		ft_error("Incorrect magic-header in file!");
	if (read(asmb->fd, asmb->prog_name, PROG_NAME_LENGTH) == 0)
		ft_error("Not enough data in file!");
	if (read(asmb->fd, null, 4) == 0)
		ft_error("Not enough data in file!");
	if (read(asmb->fd, &asmb->prog_size, 4) == 0)
		ft_error("Not enough data in file!");
	asmb->prog_size = reverse_bytes(asmb->prog_size, 4);
	if (read(asmb->fd, asmb->comment, COMMENT_LENGTH) == 0)
		ft_error("Not enough data in file!");
	if (read(asmb->fd, null, 4) == 0)
		ft_error("Not enough data in file!");
}

char			write_t_reg(command)
{
	
}

char			write_t_ind(command)
{

}

char			write_t_dir(command)
{

}

static char		check_codage(t_command *command)
{
	int		i;

	i = 3;
	while (i > 0)
	{
		if (!(command->codage & 128) && (command->codage & 64))
			if (write_t_reg(command))
				return (1);
		if ((command->codage & 128) && (command->codage & 64))
			if (write_t_ind(command))
				return (1);
		if ((command->codage & 128) && !(command->codage & 64))
			if (write_t_dir(command))
				return (1);
		i--;
		command->codage <<= 2;
	}
	return (0);
}

static void		read_executable(t_asm *asmb)
{
	t_command 		*command;
	unsigned char	buf[1];

	if (read(asmb->fd, buf, 1) != 0)
	{
		command = initial_command(asmb);
		command->opcode = buf[0];
		if (read(asmb->fd, buf, 1) == 0)
			;// break ;
		command->codage = buf[0];
		ft_printf("%d\n", command->opcode); //DELETE IT!!!!!!
		ft_printf("%d\n", command->codage);	//DELETE IT!!!!!!
		if (check_codage(command))
			;// break ;			
	}
}

int				main(void)
{
	t_asm			*asmb;

	/*********** DELETE IT ****************/
	asmb = init_asmb();
	asmb->fd = open("toto.cor", O_RDONLY);
	/**************************************/

	read_info(asmb);
	read_executable(asmb);

	ft_printf("name: %s\n", asmb->prog_name);
	ft_printf("size: %d\n", asmb->prog_size);
	ft_printf("comment: %s\n", asmb->comment);
	return (0);
}
