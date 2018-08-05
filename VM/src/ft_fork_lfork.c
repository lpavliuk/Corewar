#include "corewar.h"

void	copy_new_process(t_process **head, t_process *process_old,
		short position)
{
	t_process	*process;
	int			i;

	i = 1;
	process = (t_process *)malloc(sizeof(t_process));
	(!process) ? ft_error("Error") : 0;
	while (i <= REG_NUMBER)
	{
		process->registries[i] = process->registries[i];
		i++;
	}
	process->parent = process->parent;
	process->position = position;
	(g_vm->flag_visual) ? TURN_ON_PROCESS : 1;
	process->carry = process->carry;
	process->live = process->live;
	process->opcode = 0;
	process->codage = process->codage;
	process->cycles_to_perform = 0;
	process->next = NULL;
	if (*head)
		process->next = *head;
	*head = process;
	(g_vm->process_count)++;
}

void	ft_fork(t_process *process)
{
	int new_position;
	// static long long i = 0;

	new_position = ((get_arg((process->position + 1) % MEM_SIZE, T_DIR_SIZE))
		% IDX_MOD);
	// (new_position < 0) ? (new_position += 4096) : 1;
	// fprintf(g_f, "ft_fork:			in cycle ->%d<- process_position is ->%d<- __uints: new_pos %u __short  new pos %hd process count %d\n", g_vm->cur_cycle, process->position, new_position, new_position, g_vm->process_count);
	copy_new_process(&(g_vm->process), process, (new_position + process->position) % MEM_SIZE);
	if (g_vm->flag_visual)
		SET_PIXEL_COLOR;
	process->position = (process->position + T_DIR_SIZE + 1) % MEM_SIZE;
	if (g_vm->flag_visual)
		TURN_ON_PROCESS;
	// i++;
}

void	ft_lfork(t_process *process)
{
	unsigned short new_position;

	new_position = (process->position
		+ ((get_arg((process->position + 1) % MEM_SIZE, T_DIR_SIZE))))
			% MEM_SIZE;
	// (new_position < 0) ? (new_position += 4096) : 1;
	copy_new_process(&(g_vm->process), process, new_position);
	if (g_vm->flag_visual)
		SET_PIXEL_COLOR;
	process->position = (process->position + T_DIR_SIZE + 1) % MEM_SIZE;
	if (g_vm->flag_visual)
		TURN_ON_PROCESS;
}
