#include "corewar.h"

/* WITH IDX_MOD OR NOT??????? */

int		ft_and_or_xor_args(unsigned int *args, char *codage,
	t_process *process, char offset)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (codage[i] == IND_CODE && (offset += T_IND_SIZE))
			args[i] = get_arg((process->position + get_arg((process->position +
			(offset - T_IND_SIZE)) % MEM_SIZE, T_IND_SIZE))
				% MEM_SIZE, T_IND_READ);
		else if (codage[i] == REG_CODE)
		{
			args[i] = get_arg((process->position + offset)
				% MEM_SIZE, T_REG_SIZE);
			offset += T_REG_SIZE;
			if (args[i] < 1 || args[i] > 16)
				return (0);
		}
		else if (codage[i] == DIR_CODE && (offset += LABEL_SIZE(OPCODE(6)))) /* LABEL_SIZE(OPCODE(6)) == LABEL_SIZE(OPCODE(7 && 8))*/
			args[i] = get_arg((process->position
			+ (offset - LABEL_SIZE(OPCODE(6)))) % MEM_SIZE, LABEL_SIZE(OPCODE(6)));
		i++;
	}
	return (1);
}

void	ft_and(t_process *process)
{
	char			codage[4];
	unsigned int	args[3];

	decipher_codage(codage, COUNT_ARGS(OPCODE(5)), GET_CODAGE);
	if (check_valid_codage(OPCODE(5), codage) && ft_and_or_xor_args(args,
		codage, process, 2))
	{
		process->registries[args[2]] = ((codage[0] == REG_CODE) ?
			process->registries[args[0]] : args[0]) & ((codage[1] == REG_CODE) ?
			process->registries[args[1]] : args[1]);
		process->carry = (process->registries[args[2]]) ? 0 : 1;
	}
	// ft_printf("____AND: process->position before changes %d\n", process->position);
	change_process_position(OPCODE(5), codage, process);
	// ft_printf("____AND: process->position after changes %d\n", process->position);
}

void	ft_or(t_process *process)
{
	char			codage[4];
	unsigned int	args[3];

	decipher_codage(codage, COUNT_ARGS(7), GET_CODAGE);
	if (check_valid_codage(OPCODE(6), codage) && ft_and_or_xor_args(args,
		codage, process, 2))
	{
		process->registries[args[2]] = ((codage[0] == REG_CODE) ?
			process->registries[args[0]] : args[0]) | ((codage[1] == REG_CODE) ?
			process->registries[args[1]] : args[1]);
		process->carry = (process->registries[args[2]]) ? 0 : 1;
	}
	// ft_printf("____OR: process->position before changes %d\n", process->position);
	change_process_position(OPCODE(6), codage, process);
	// ft_printf("____OR: process->position after changes %d\n", process->position);
}

void	ft_xor(t_process *process)
{
	char			codage[4];
	unsigned int	args[3];

	decipher_codage(codage, COUNT_ARGS(8), GET_CODAGE);
	if (check_valid_codage(OPCODE(7), codage) && ft_and_or_xor_args(args,
		codage, process, 2))
	{
		process->registries[args[2]] = ((codage[0] == REG_CODE) ?
			process->registries[args[0]] : args[0]) ^ ((codage[1] == REG_CODE) ?
			process->registries[args[1]] : args[1]);
		process->carry = (process->registries[args[2]]) ? 0 : 1;
	}
	// ft_printf("____XOR: process->position before changes %d\n", process->position);
	change_process_position(OPCODE(7), codage, process);
	// ft_printf("____XOR: process->position after changes %d\n", process->position);
}
