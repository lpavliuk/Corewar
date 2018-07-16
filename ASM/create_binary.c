/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_binary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 13:32:46 by opavliuk          #+#    #+#             */
/*   Updated: 2018/07/12 13:32:47 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		input_info(t_asm *asmb)
{
	char	null[4];

	ft_bzero(null, 4);

	write(asmb->new_fd, &asmb->magic, 4);
	write(asmb->new_fd, &asmb->prog_name, PROG_NAME_LENGTH);
	write(asmb->new_fd, &null, 4);
	write(asmb->new_fd, &asmb->prog_size, 4);
	write(asmb->new_fd, &asmb->comment, COMMENT_LENGTH);
	write(asmb->new_fd, &null, 4);
}

void		input_executable(t_command *command, t_asm *asmb)
{
	write(asmb->new_fd, &command->opcode, 1);
	write(asmb->new_fd, &command->codage, 1);
	write(asmb->new_fd, &command->arg1, 1);
	write(asmb->new_fd, &command->arg2, 2);
	write(asmb->new_fd, &command->arg3, 2);
}

unsigned int reverse_bytes(unsigned int x, char bytes)
{
	unsigned int reversed;
	unsigned char *n1;
	unsigned char *n2;

	n1 = (unsigned char *)&x;
	n2 = (unsigned char *)&reversed;

	if (bytes == 2)
	{
		n2[0] = n1[1];
		n2[1] = n1[0];
	}
	else
	{
		n2[0] = n1[3];
		n2[1] = n1[2];
		n2[2] = n1[1]; 
		n2[3] = n1[0];
	}

	return (reversed);
}

int		main(void)
{
	t_asm		*asmb;
	t_command	*command;

	/***********************INITIAL***********************************/
	asmb = malloc(sizeof(t_asm));
	asmb->magic = COREWAR_EXEC_MAGIC;
	ft_bzero(asmb->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(asmb->comment, COMMENT_LENGTH + 1);
	asmb->file_name = "name.cor";
	asmb->new_fd = 0;
	asmb->prog_size = 15;

	ft_strcat(asmb->prog_name, "name");
	ft_strcat(asmb->comment, "comment");

	command = malloc(sizeof(t_command));
	command->codage = 104;
	command->bytes = 7;
	command->bytes_before = 0;
	command->opcode = 11;
	command->label = "l2";
	command->arg1 = 1;
	command->arg2 = 7;
	command->arg3 = 0;
	command->next = NULL;
	/*****************************************************************/

	asmb->magic = reverse_bytes(asmb->magic, 4);
	asmb->prog_size = reverse_bytes(asmb->prog_size, 4);
	
	command->arg2 = reverse_bytes(command->arg2, 2);

	asmb->new_fd = open(asmb->file_name, O_RDWR | O_TRUNC | O_CREAT, 0777);

	input_info(asmb); 						// Writes bots name, comment and size to the file
	while (command)
	{
		input_executable(command, asmb);	// Writes bots commands to the file
		command = command->next;
	}

	close(asmb->new_fd);
	
	return (0);
}
