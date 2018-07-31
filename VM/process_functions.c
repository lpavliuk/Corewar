#include "corewar.h"

void	ft_live(t_process *process, t_vm *vm)
{
	process->live = 1;
	if (get_arg(process->position, LABEL_SIZE(process->opcode))
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

}

void	ft_st(t_process *process, t_vm *vm)
{

}

void	ft_add(t_process *process, t_vm *vm)
{

}

void	ft_sub(t_process *process, t_vm *vm)
{

}

void	ft_and(t_process *process, t_vm *vm)
{

}

void	ft_or(t_process *process, t_vm *vm)
{

}

void	ft_xor(t_process *process, t_vm *vm)
{

}

void	ft_zjmp(t_process *process, t_vm *vm)
{

}

void	ft_ldi(t_process *process, t_vm *vm)
{

}

void	ft_sti(t_process *process, t_vm *vm)
{

}

void	ft_fork(t_process *process, t_vm *vm)
{

}

void	ft_lld(t_process *process, t_vm *vm)
{

}

void	ft_lldi(t_process *process, t_vm *vm)
{

}

void	ft_lfork(t_process *process, t_vm *vm)
{

}

void	ft_aff(t_process *process, t_vm *vm)
{

}
