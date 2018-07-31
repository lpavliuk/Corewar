#include "corewar.h"

int		check_valid_codage(char opcode, char *codage)
{
	char	input_arg;
	char	possible_arg;
	char	it_was;

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

void	change_process_position_by_codage()
{

}

void	ft_ld(t_process *process, t_vm *vm)
{
	char			codage[4];
	unsigned int	arg;
	unsigned int	result;

	decipher_codage(codage, COUNT_ARGS(2), (process->position + 1) % MEM_SIZE);
	if (check_valid_codage(OPCODE(1), codage) && )
	{
		result = get_arg((process->position + ((codage[0] == IND_CODE)
			? (get_arg((process->position + (get_arg((process->position + 2)
			% MEM_SIZE, T_IND_SIZE) % IDX_MOD)) % MEM_SIZE, T_IND_READ)) : 2))
			% MEM_SIZE, T_DIR_SIZE);
		arg = get_arg((process->position + ((codage[0] == IND_CODE) ? 2 : 4))
			% MEM_SIZE, T_REG_SIZE);
		process->registries[arg] = result;
		process->position = ((codage[0] == IND_CODE) ? 2 : 4) + 3; /* offset is (codage + arg1(T_IND || T_DIR) + arg2 + 1) */
	}
	else
		change_process_position_at_wrong_codage();
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
