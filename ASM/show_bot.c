/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_bot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 12:54:31 by opavliuk          #+#    #+#             */
/*   Updated: 2018/07/16 12:54:35 by opavliuk         ###   ########.fr       */
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

	command->next = NULL;

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

	command->next->next = NULL;

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

	command->next->next->next = NULL;

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

	command->next->next->next->next = NULL;

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

	command->next->next->next->next->next = NULL;

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
}
/****************************************************************************/

static void write_bites(unsigned int num_value, char bytes)
{
	unsigned char *num;

	num = (unsigned char *)&num_value;
	if (bytes == 2)
		ft_printf("%-3d %-3d%11c", num[1], num[0], ' ');
	else if (bytes == 4)
		ft_printf("%-3d %-3d %-3d %-3d%3c", num[3], num[2], num[1], num[0], ' ');
}

static void	write_str_or_num(char str, t_arg *arg)
{
	while (arg)
	{
		if (str == 1 && arg->str_value)
		{
			if (arg->type == 1)
				ft_printf("%%:%-16s", arg->str_value);
			else
				ft_printf(":%-17s", arg->str_value);
		}
		else if (str == 1)
		{
			if (arg->type == 0)
				ft_printf("r");
			else if (arg->type == 1)
				ft_printf("%%");
			ft_printf("%-17d", arg->num_value);
		}
		else if (str == 16 && arg->type != 0)
			write_bites((unsigned int)arg->num_value, arg->arg_size);
		else
			ft_printf("%-18d", arg->num_value);
		arg = arg->next;
	}
}

int		main(void)
{
	t_asm		*asmb;
	t_command	*command;

	/***********************INITIAL***********************************/
	asmb = malloc(sizeof(t_asm));
	command = malloc(sizeof(t_command));
	initial(asmb, command);
	/****************************************************************/

	ft_printf("Dumping annotated program on standard output\n");
	ft_printf("Program size : %d bytes\n", asmb->prog_size);
	ft_printf("Name : \"%s\"\n", asmb->prog_name);
	ft_printf("Comment : \"%s\"\n\n", asmb->comment);

	while (command)
	{
		if (command->labels && command->labels->content)
			ft_printf("%-11d:%4c%s:\n", command->bb, ' ', command->labels->content);
		ft_printf("%-5d(%-3d) :", command->bb, command->bytes);
		ft_printf("%8c%-10s",  ' ', command->name);
		write_str_or_num(1, command->args);
		ft_printf("\n%20c", ' ');
		if (command->codage)
			ft_printf("%-4d%-6d", command->opcode, command->codage);
		else
			ft_printf("%-10d", command->opcode);
		write_str_or_num(16, command->args);
		ft_printf("\n%20c", ' ');
		if (command->codage)
			ft_printf("%-4d%-6d", command->opcode, command->codage);
		else
			ft_printf("%-10d", command->opcode);
		write_str_or_num(0, command->args);
		ft_printf("\n\n");
		command = command->next;
	}
	return (0);
}
