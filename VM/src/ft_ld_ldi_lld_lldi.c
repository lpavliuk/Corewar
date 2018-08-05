#include "corewar.h"

void	ft_ld(t_process *process)
{
	char			codage[4];
	unsigned int	arg2;
	unsigned int	result;

	decipher_codage(codage, COUNT_ARGS(2), GET_CODAGE);
	if (check_valid_codage(OPCODE(1), codage)
	&& (arg2 = get_arg((process->position + ((codage[0] == IND_CODE) ? 2 : 4)
		+ 2) % MEM_SIZE, T_REG_SIZE)) > 0 && arg2 < 17)
	{
		result = (codage[0] == IND_CODE) ? (get_arg((process->position
		+ (get_arg((process->position + 2) % MEM_SIZE, T_IND_SIZE) % IDX_MOD)),
			T_IND_READ)) : (get_arg((process->position + 2)
			% MEM_SIZE, LABEL_SIZE(OPCODE(1))));
		process->registries[arg2] = result;
		// fprintf(g_f, "ft_ld: in cycle ->%d<- process_position is ->%d<- __uints: arg2 %u result %u__  __short arg2 %hd result %hd__ reg[arg2] = %u carry %d\n",
		// 		g_vm->cur_cycle, process->position, arg2, result, arg2, result, process->registries[arg2], process->carry);
		process->carry = (result) ? 0 : 1;
	}
	change_process_position(OPCODE(1), codage, process);
}

void	ft_lld(t_process *process)
{
	char			codage[4];
	unsigned int	arg2;
	unsigned int	result;

	decipher_codage(codage, COUNT_ARGS(13), GET_CODAGE);
	if (check_valid_codage(OPCODE(12), codage)
	&& (arg2 = get_arg((process->position + ((codage[0] == IND_CODE) ? 2 : 4))
			% MEM_SIZE, T_REG_SIZE)) > 1 && arg2 < 17)
	{
		result = (codage[0] == IND_CODE) ? (get_arg((process->position
		+ get_arg((process->position + 2) % MEM_SIZE, T_IND_SIZE))
		% MEM_SIZE, T_IND_READ)) : (get_arg((process->position + 2) % MEM_SIZE,
			LABEL_SIZE(OPCODE(12))));
		process->registries[arg2] = result;
		process->carry = (result) ? 0 : 1;
	}
	change_process_position(OPCODE(12), codage, process);
}

int		ft_ldi_lldi_check_args(unsigned int *uargs, short int *sargs,
	char *codage, t_process *process)
{
	int		i;
	char	offset;

	i = 0;
	offset = 2;
	while (i < 3)
	{
		if (codage[i] == IND_CODE && (offset += T_IND_SIZE))
			uargs[i] = get_arg((process->position + (get_arg((process->position
			+ 2) % MEM_SIZE, T_IND_SIZE) % IDX_MOD)) % MEM_SIZE, T_IND_READ);
		else if (codage[i] == REG_CODE)
		{
			uargs[i] = get_arg((process->position + offset)
				% MEM_SIZE, T_REG_SIZE);
			offset += T_REG_SIZE;
			if (uargs[i] < 1 || uargs[i] > 16)
				return (0);
		}
		else if (codage[i] == DIR_CODE && (offset += LABEL_SIZE(OPCODE(9)))) /* LABEL_SIZE(OPCODE(9)) == LABEL_SIZE(OPCODE(13))*/
			sargs[i] = (short)get_arg((process->position
			+ (offset - LABEL_SIZE(OPCODE(9)))) % MEM_SIZE, T_DIR_SIZE);
		i++;
	}
	return (1);
}

void	ft_ldi(t_process *process)
{
	char			codage[4];
	unsigned int	uargs[3];
	short int		sargs[2];
	unsigned int	result;

	decipher_codage(codage, COUNT_ARGS(10), GET_CODAGE);
	if (check_valid_codage(OPCODE(9), codage) && ft_ldi_lldi_check_args(uargs,
		sargs, codage, process))
	{
		result = get_arg((process->position
			+ ((((codage[0] == DIR_CODE) ? sargs[0] : uargs[0])
			+ ((codage[1] == DIR_CODE) ? sargs[1] : uargs[1])) % IDX_MOD))
			% MEM_SIZE, T_IND_READ);
		process->registries[uargs[2]] = result;
	}
	change_process_position(OPCODE(9), codage, process);
}

void	ft_lldi(t_process *process)
{
	char			codage[4];
	unsigned int	uargs[3];
	short int		sargs[2];
	unsigned int	result;

	decipher_codage(codage, COUNT_ARGS(14), GET_CODAGE);
	if (check_valid_codage(OPCODE(13), codage) && ft_ldi_lldi_check_args(uargs,
		sargs, codage, process))
	{
		result = get_arg((process->position
			+ ((codage[0] == DIR_CODE) ? sargs[0] : uargs[0])
			+ ((codage[1] == DIR_CODE) ? sargs[1] : uargs[1]))
			% MEM_SIZE, T_IND_READ);
		process->registries[uargs[2]] = result;
		process->carry = (result) ? 0 : 1;
	}
	change_process_position(OPCODE(13), codage, process);
}
