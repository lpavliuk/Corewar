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

#include "../asm.h"

static void			input_info(t_asm *asmb)
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

unsigned int		reverse_bytes(unsigned int x, char bytes)
{
	unsigned int	reversed;
	unsigned char	*n1;
	unsigned char	*n2;

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
	return ((bytes == 1) ? x : reversed);
}

static void			input_executable(t_command *command, t_arg *args, int fd)
{
	write(fd, &command->opcode, 1);
	if (command->codage)
		write(fd, &command->codage, 1);
	while (args)
	{
		args->num_value = reverse_bytes(args->num_value, args->arg_size);
		write(fd, &args->num_value, args->arg_size);
		args = args->next;
	}
}

void				create_binary(t_asm *asmb, t_command *command)
{
	asmb->magic = reverse_bytes(asmb->magic, 4);
	asmb->prog_size = reverse_bytes(asmb->prog_size, 4);
	asmb->new_fd = open(asmb->file_name, O_RDWR | O_TRUNC | O_CREAT, 0777);
	input_info(asmb);
	while (command)
	{
		input_executable(command, command->args, asmb->new_fd);
		command = command->next;
	}
	close(asmb->new_fd);
}
