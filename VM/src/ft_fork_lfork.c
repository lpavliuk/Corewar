#include "corewar.h"

void	copy_new_process(t_process **head, t_process *process,
		short position)
{
	t_process	*new;
	int			i;

	i = 1;
	new = (t_process *)malloc(sizeof(t_process));
	(!new) ? ft_error("Error") : 0;
	while (i <= REG_NUMBER)
	{
		new->registries[i] = process->registries[i];
		i++;
	}
	new->parent = process->parent;
	new->position = position;
	(g_vm->flag_visual) ? TURN_ON_PROCESS : 1;
	new->carry = process->carry;
	new->live = process->live;
	new->opcode = process->opcode;
	new->codage = process->codage;
	new->cycles_to_perform = 0;
	new->next = NULL;
	if (*head)
		new->next = *head;
	*head = new;
	(g_vm->process_count)++;
}

void	ft_fork(t_process *process)
{
	short	new_position;
	static long long i = 0;

	new_position = (short)((get_arg((process->position + 1) % MEM_SIZE, T_DIR_SIZE)
		% IDX_MOD) + process->position) % MEM_SIZE;
	fprintf(g_f, "ft_fork:			in cycle ->%d<- process_position is ->%d<- __uints: new_pos %u __short  new pos %hd process count %d\n", g_vm->cur_cycle, process->position, new_position, new_position, g_vm->process_count);
	copy_new_process(&(g_vm->process), process, new_position);
	if (g_vm->flag_visual)
		SET_PIXEL_COLOR;
	process->position = (process->position + T_DIR_SIZE + 1) % MEM_SIZE;
	if (g_vm->flag_visual)
		TURN_ON_PROCESS;
	i++;
}

void	ft_lfork(t_process *process)
{
	short new_position;

	new_position = (get_arg((process->position + 1) % MEM_SIZE, T_DIR_SIZE)
		+ process->position) % MEM_SIZE;
	copy_new_process(&(g_vm->process), process, new_position);
	if (g_vm->flag_visual)
		SET_PIXEL_COLOR;
	process->position = (process->position + T_DIR_SIZE + 1) % MEM_SIZE;
	if (g_vm->flag_visual)
		TURN_ON_PROCESS;
}
