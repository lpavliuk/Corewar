#include "corewar.h"

void	ft_live(t_process *process, t_vm *vm)
{
	process->live = 1;
	if (get_arg((process->position + 1) % MEM_SIZE, LABEL_SIZE(process->opcode))
		== process->parent->id)
	{
		process->parent->lives_cur_period++;
		process->parent->last_live = vm->cur_cycle;
	}
	if (vm->flag_visual)
		g_pixels[process->position]->live = 50;
}

void	ft_ld(t_process *process, t_vm *vm)
{
	char			codage[4];
	unsigned int	ar1;
	unsigned int	ar2;
	unsigned int	result;

	decipher_codage(codage, COUNT_ARGS(2), (process->position + 1) % MEM_SIZE);
	if (codage[0] == IND_CODE)
	{
		ar1 = get_arg((process->position + 2) % MEM_SIZE, T_IND_SIZE) % IDX_MOD;
		result = get_arg((process->position + ar1) % MEM_SIZE, T_IND_READ);
		ar2 = get_arg((process->position + 4) % MEM_SIZE, T_REG_SIZE);
	}
	else
	{
		result = get_arg((process->position + 2) % MEM_SIZE, T_DIR_SIZE);
		ar2 = get_arg((process->position + 3) % MEM_SIZE, T_REG_SIZE);
	}
	process->registries[ar2] = result;
}

// void	ft_st(t_process *process, t_vm *vm)
// {

// }

// void	ft_add(t_process *process, t_vm *vm)
// {

// }

// void	ft_sub(t_process *process, t_vm *vm)
// {

// }

// void	ft_and(t_process *process, t_vm *vm)
// {

// }

// void	ft_or(t_process *process, t_vm *vm)
// {

// }

// void	ft_xor(t_process *process, t_vm *vm)
// {

// }

// void	ft_zjmp(t_process *process, t_vm *vm)
// {

// }

// void	ft_ldi(t_process *process, t_vm *vm)
// {

// }

// void	ft_sti(t_process *process, t_vm *vm)
// {

// }

// void	ft_fork(t_process *process, t_vm *vm)
// {

// }

// void	ft_lld(t_process *process, t_vm *vm)
// {

// }

// void	ft_lldi(t_process *process, t_vm *vm)
// {

// }

// void	ft_lfork(t_process *process, t_vm *vm)
// {

// }

// void	ft_aff(t_process *process, t_vm *vm)
// {

// }
