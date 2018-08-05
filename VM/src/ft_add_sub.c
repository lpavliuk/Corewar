#include "corewar.h"

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
			args[i] = get_arg((process->position + 1 + (i + T_REG_SIZE)) % MEM_SIZE,
					T_REG_SIZE);
			if (!(args[i] > 0 && args[i] < 17))
			{
				// fprintf(g_f, "ft_add: !(args[i] > 0 && args[i] < 17)) when arg[i] == %u\n", args[i]);
				break ;
			}
			i++;
		}
		if (i == 3)
		{
			process->registries[args[2]] = process->registries[args[0]]
			+ process->registries[args[1]];
			process->carry = (process->registries[args[2]]) ? 0 : 1;
			// fprintf(g_f, "ft_add: in cycle ->%d<- process_position is ->%d<- __uints: arg0 %u arg1 %u__  __short arg0 %hd arg1 %hd__ reg[0] = %u reg[1] = %u reg[2] = %u carry %d\n",
				// g_vm->cur_cycle, process->position, args[0], args[1], args[0], args[1], process->registries[args[0]], process->registries[args[1]], process->registries[args[2]], process->carry);
		}
	}
	// else
		// fprintf(g_f, "ft_add: !if\n");
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
			args[i] = get_arg((process->position + 1 + (i + T_REG_SIZE)) % MEM_SIZE,
					T_REG_SIZE);
			if (!(args[i] > 0 && args[i] < 17))
			{
				// fprintf(g_f, "ft_sub: !(args[i] > 0 && args[i] < 17)) when arg[i] == %u\n", args[i]);
				break ;
			}
			i++;
		}
		if (i == 3)
		{
			process->registries[args[2]] = process->registries[args[0]]
			- process->registries[args[1]];
			process->carry = (process->registries[args[2]] != 0) ? 0 : 1;
			// fprintf(g_f, "ft_sub: in cycle ->%d<- process_position is ->%d<- __uints: arg0 %u arg1 %u__  __short arg0 %hd arg1 %hd__ reg[0] = %u reg[1] = %u reg[2] = %u carry %d\n",
				// g_vm->cur_cycle, process->position, args[0], args[1], args[0], args[1], process->registries[args[0]], process->registries[args[1]], process->registries[args[2]], process->carry);
		}
	}
		// else
		// fprintf(g_f, "ft_sub: !if\n");
	change_process_position(OPCODE(4), codage, process);
}
