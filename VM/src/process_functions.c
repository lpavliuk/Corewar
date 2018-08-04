#include "corewar.h"

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

void	ft_add(t_process *process)
{
	int				i;
	char			codage[4];
	unsigned char	args[3];

	i = 0;
	decipher_codage(codage, COUNT_ARGS(4), GET_CODAGE);
	if (check_valid_codage(OPCODE(3), codage))
	{
		while(i < 3)
		{
			args[i] = get_arg((process->position + (i + T_REG_SIZE)) % MEM_SIZE,
					T_REG_SIZE);
			if (!(args[i] > 0 && args[i] < 17))
				break ;
			i++;
		}
		if (i == 3)
		{
			process->registries[args[2]] = process->registries[args[0]]
			+ process->registries[args[1]];
			process->carry = (process->registries[args[2]]) ? 0 : 1;
		}
	}
	change_process_position(OPCODE(3), codage, process);
}

void	ft_sub(t_process *process)
{
	int				i;
	char			codage[4];
	unsigned char	args[3];

	i = 0;
	decipher_codage(codage, COUNT_ARGS(5), GET_CODAGE);
	if (check_valid_codage(OPCODE(4), codage))
	{
		while(i < 3)
		{
			args[i] = get_arg((process->position + (i + T_REG_SIZE)) % MEM_SIZE,
					T_REG_SIZE);
			if (!(args[i] > 0 && args[i] < 17))
				break ;
			i++;
		}
		if (i == 3)
		{
			process->registries[args[2]] = process->registries[args[0]]
			- process->registries[args[1]];
			process->carry = (process->registries[args[2]]) ? 0 : 1;
		}
	}
	change_process_position(OPCODE(4), codage, process);
}

void	ft_zjmp(t_process *process)
{
	if (g_vm->flag_visual)
		SET_PIXEL_COLOR;
	if (process->carry)
		process->position += (short)get_arg(((process->position + 1) % IDX_MOD),
			T_DIR_SIZE);
	else
		process->position = (process->position + 1 + T_DIR_SIZE) % MEM_SIZE;
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
