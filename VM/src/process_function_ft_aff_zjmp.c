#include "corewar.h"
#include <stdio.h>
int		check_valid_codage(char opcode, char *codage)
{
	int		input_arg;
	int		possible_arg;
	int		it_was;

	input_arg = 0;
	while(input_arg < COUNT_ARGS(opcode))
	{
		possible_arg = 0;
		it_was = 0;
		while(possible_arg < 3)
		{
			if (ARG(opcode, input_arg, possible_arg)
				&& codage[input_arg] == possible_arg + 1)
				it_was = 1;
			possible_arg++;
		}
		if (!it_was)
			return (0);
		input_arg++;
	}
	return (1);
}

void	change_process_position(char opcode, char *codage, t_process *process)
{
	char	offset;
	int		i;

	offset = 0;
	i = 0;
	while (i < 3)
	{
		(codage[i] == IND_CODE) ? (offset += T_IND_SIZE) : 0;
		(codage[i] == REG_CODE) ? (offset += T_REG_SIZE) : 0;
		(codage[i] == DIR_CODE) ? (offset += LABEL_SIZE(opcode)) : 0;
		i++;
	}
	(g_vm->flag_visual) ? (g_pixels[process->position]->color =
				g_pixels[process->position]->color % 10) : 0;
	process->position = ((process->position) + offset + 1 + CODAGE(opcode))
		% MEM_SIZE;
	(g_vm->flag_visual) ? (g_pixels[process->position]->color =
				(g_pixels[process->position]->color % 10) + 20) : 0;
}

void	ft_zjmp(t_process *process)
{
	if (g_vm->flag_visual)
		SET_PIXEL_COLOR;
	if (process->carry)
	{
		fprintf(g_f, "zjmp: in cycle ->%d<- process_position is ->%d<- carry 1\n", g_vm->cur_cycle, process->position);
		process->position += (short)get_arg(((process->position + 1) % IDX_MOD),
			T_DIR_SIZE);
		fprintf(g_f, "					process_position is ->%d<- carry 1\n", process->position);
	}
	else
	{
		fprintf(g_f, "zjmp: in cycle ->%d<- process_position is ->%d<- carry 0\n", g_vm->cur_cycle, process->position);
		process->position = (process->position + 1 + T_DIR_SIZE) % MEM_SIZE;
		fprintf(g_f, "					process_position is ->%d<- carry 0\n", process->position);
	}
	if (g_vm->flag_visual)
		TURN_ON_PROCESS;
}

/* WTF-FUNCTION */

void	ft_aff(t_process *process)
{
	char			codage[4];
	unsigned int	reg_num;

	decipher_codage(codage, COUNT_ARGS(16), GET_CODAGE);
	if (codage[0] == REG_CODE)
	{
		reg_num = get_arg((process->position + 1) % MEM_SIZE, T_REG_SIZE);
		if (reg_num > 0 && reg_num < 17 && !g_vm->flag_visual)
			ft_printf("%c", process->registries[reg_num]);
	}
	change_process_position(OPCODE(15), codage, process);
}
