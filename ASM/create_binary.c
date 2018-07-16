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

/************************** DELETE IT!!!! ************************************/
void	initial(t_asm *asmb, t_command *command)
{
	asmb->magic = COREWAR_EXEC_MAGIC;
	ft_bzero(asmb->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(asmb->comment, COMMENT_LENGTH + 1);
	asmb->file_name = "name.cor";
	asmb->new_fd = 0;
	asmb->prog_size = 320;

	ft_strcat(asmb->prog_name, "Jumper !");
	ft_strcat(asmb->comment, "en fait C forker !");

	// COMMAND #1
	command->name = "st";
	command->opcode = 3;
	command->bytes = 5;
	command->bb = 0;
	command->codage = 112;

	/******initial args*******/
	command->args = malloc(sizeof(t_arg));
	command->args->str_value = NULL;
	command->args->num_value = 1;
	command->args->arg_size = 1;
	command->args->type = 0;
	command->args->next = malloc(sizeof(t_arg));
	command->args->next->str_value = "buff";
	command->args->next->num_value = 73;
	command->args->next->arg_size = 2;
	command->args->next->type = 2;
	command->args->next->next = NULL;
	/***********************/

	command->labels = malloc(sizeof(t_list));
	command->labels->content = "gobepc";

    // COMMAND #2
    command->next = malloc(sizeof(t_command));
	command->next->name = "st";
	command->next->opcode = 3;
	command->next->bytes = 5;
	command->next->bb = 5;
	command->next->codage = 112;

	/******initial args*******/
	command->next->args = malloc(sizeof(t_arg));
	command->next->args->str_value = NULL;
	command->next->args->num_value = 6;
	command->next->args->arg_size = 1;
	command->next->args->type = 0;
	command->next->args->next = malloc(sizeof(t_arg));
	command->next->args->next->str_value = NULL;
	command->next->args->next->num_value = -4;
	command->next->args->next->arg_size = 2;
	command->next->args->next->type = 2;
	command->next->args->next->next = NULL;
	/***********************/

	command->next->labels = malloc(sizeof(t_list));
	command->next->labels->content = NULL;


	// COMMAND #3
    command->next->next = malloc(sizeof(t_command));
	command->next->next->name = "ld";
	command->next->next->opcode = 2;
	command->next->next->bytes = 5;
	command->next->next->bb = 10;
	command->next->next->codage = 208;

	/******initial args*******/
	command->next->next->args = malloc(sizeof(t_arg));
	command->next->next->args->str_value = "buff";
	command->next->next->args->num_value = 63;
	command->next->next->args->arg_size = 2;
	command->next->next->args->type = 2;
	command->next->next->args->next = malloc(sizeof(t_arg));
	command->next->next->args->next->str_value = NULL;
	command->next->next->args->next->num_value = 1;
	command->next->next->args->next->arg_size = 1;
	command->next->next->args->next->type = 0;
	command->next->next->args->next->next = NULL;
	/***********************/

	command->next->next->labels = malloc(sizeof(t_list));
	command->next->next->labels->content = NULL;


	// COMMAND #4
    command->next->next->next = malloc(sizeof(t_command));
	command->next->next->next->name = "ld";
	command->next->next->next->opcode = 2;
	command->next->next->next->bytes = 7;
	command->next->next->next->bb = 15;
	command->next->next->next->codage = 144;

	/******initial args*******/
	command->next->next->next->args = malloc(sizeof(t_arg));
	command->next->next->next->args->str_value = NULL;
	command->next->next->next->args->num_value = 0;
	command->next->next->next->args->arg_size = 4;
	command->next->next->next->args->type = 1;
	command->next->next->next->args->next = malloc(sizeof(t_arg));
	command->next->next->next->args->next->str_value = NULL;
	command->next->next->next->args->next->num_value = 7;
	command->next->next->next->args->next->arg_size = 1;
	command->next->next->next->args->next->type = 0;
	command->next->next->next->args->next->next = NULL;
	/***********************/

	command->next->next->next->labels = malloc(sizeof(t_list));
	command->next->next->next->labels->content = "debut";

	// COMMAND #5
    command->next->next->next->next = malloc(sizeof(t_command));
	command->next->next->next->next->name = "zjmp";
	command->next->next->next->next->opcode = 9;
	command->next->next->next->next->bytes = 3;
	command->next->next->next->next->bb = 22;
	command->next->next->next->next->codage = 0;

	/******initial args*******/
	command->next->next->next->next->args = malloc(sizeof(t_arg));
	command->next->next->next->next->args->str_value = "suite";
	command->next->next->next->next->args->num_value = 55;
	command->next->next->next->next->args->arg_size = 2;
	command->next->next->next->next->args->type = 1;
	command->next->next->next->next->args->next = NULL;
	/***********************/

	command->next->next->next->next->labels = NULL;

	// COMMAND #6
    command->next->next->next->next->next = malloc(sizeof(t_command));
	command->next->next->next->next->next->name = "live";
	command->next->next->next->next->next->opcode = 1;
	command->next->next->next->next->next->bytes = 5;
	command->next->next->next->next->next->bb = 25;
	command->next->next->next->next->next->codage = 0;

	/******initial args*******/
	command->next->next->next->next->next->args = malloc(sizeof(t_arg));
	command->next->next->next->next->next->args->str_value = NULL;
	command->next->next->next->next->next->args->num_value = 66;
	command->next->next->next->next->next->args->arg_size = 4;
	command->next->next->next->next->next->args->type = 1;
	command->next->next->next->next->next->args->next = NULL;
	/***********************/

	command->next->next->next->next->next->labels = NULL;

	
	command->next->next->next->next->next->labels = malloc(sizeof(t_list));
	command->next->next->next->next->next->labels->content = "goboucle0";

	command->next->next->next->next->next->next = NULL;	
}
/****************************************************************************/


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

int		main(void)
{
	t_asm		*asmb;
	t_command	*command;

	asmb = malloc(sizeof(t_asm));
	command = malloc(sizeof(t_command));
	initial(asmb, command);
	asmb->magic = reverse_bytes(asmb->magic, 4);
	asmb->prog_size = reverse_bytes(asmb->prog_size, 4);

	asmb->new_fd = open(asmb->file_name, O_RDWR | O_TRUNC | O_CREAT, 0777);

	input_info(asmb); 						// Writes bots name, comment and size to the file
	while (command)
	{
		input_executable(command, command->args, asmb->new_fd);	// Writes bots commands to the file
		command = command->next;
	}

	close(asmb->new_fd);

	return (0);
}
