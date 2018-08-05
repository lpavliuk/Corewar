#include "corewar.h"

void	ft_live(t_process *process)
{
	unsigned int	player_id;
	t_bot			*bot;

	process->live = 1;
	player_id = get_arg((process->position + 1) % MEM_SIZE,
		LABEL_SIZE(OPCODE(0)));
	bot = g_vm->bot;
	while (bot)
	{
		if (player_id == bot->id && (bot->last_live = g_vm->cur_cycle))
		{
			!g_vm->flag_visual
				? ft_printf("Player %d (%s) is said to be alive\n",
				bot->player_counter, bot->name) : 1;
			bot->lives_cur_period++;
		}
		bot = bot->next;
	}
	if (g_vm->flag_visual)
	{
		TURN_ON_LIVE;
		g_pixels[process->position]->counter = 50;
	}
	process->position = (process->position + 1 + 4) % MEM_SIZE;
	(g_vm->flag_visual) ? (TURN_ON_PROCESS) : 0;
}

/*
**	set_map_value() - print 4 bytes on the g_map and set appropriate values in g_pixels array
*/

void	set_map_value(t_process *process, unsigned int val,
		short int new_pstn)
{
	int		j;

	// ft_printf("%d\n", new_pstn);
	j = 0;
	while (j < 4)
	{
		g_map[(process->position + new_pstn + j) % MEM_SIZE] =
			((unsigned char *)&val)[3 - j];
		if (g_vm->flag_visual)
		{
			g_pixels[(process->position + new_pstn + j) % MEM_SIZE]->counter
				= 50;
			g_pixels[(process->position + new_pstn + j) % MEM_SIZE]->color
				= process->parent->player_counter;
		}
		j++;
	}
}

void	ft_st(t_process *process)
{
	char			codage[4];
	unsigned int	position_arg2;
	unsigned int	result;

	decipher_codage(codage, COUNT_ARGS(3), GET_CODAGE);
	if (check_valid_codage(OPCODE(2), codage) && (result = get_arg(
		(process->position + 2) % MEM_SIZE, T_REG_SIZE) > 0) && result < 17)
	{
		position_arg2 = get_arg((process->position + 3) % MEM_SIZE, ((codage[1]
			== IND_CODE) ? T_IND_SIZE : T_REG_SIZE));
		if (codage[1] == IND_CODE)
		{
			position_arg2 %= IDX_MOD;
			set_map_value(process, result, position_arg2);
		}
		else if (position_arg2 > 0 && position_arg2 <= REG_NUMBER)
			process->registries[position_arg2] = result;
	}
	change_process_position(OPCODE(2), codage, process);
}

int		ft_sti_check_args(unsigned int *args, char *codage, t_process *process,
		char offset)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (codage[i] == REG_CODE)
		{
			args[i] = get_arg((process->position + offset) % MEM_SIZE,
				T_REG_SIZE);
			offset += T_REG_SIZE;
			if (args[i] < 1 || args[i] > 16)
				return (0);
		}
		else if (codage[i] == IND_CODE && (offset += T_IND_SIZE))
			args[i] = get_arg((process->position + (get_arg((process->position
			+ (offset - T_IND_SIZE)) % MEM_SIZE, T_IND_SIZE) % IDX_MOD))
			% MEM_SIZE, T_IND_READ);
		else if (codage[i] == DIR_CODE && (offset += T_DIR_SIZE))
			args[i] = get_arg((process->position + (offset - T_DIR_SIZE))
				% MEM_SIZE, T_DIR_SIZE);
		i++;
	}
	return (1);
}

/*
**	"Значение T_REG (первый аргумент) записывается в ячейку, по адресу (текущая позиция PC плюс ((второй аргумент плюс третий аргумент) % IDX_MOD))
**	 - Если второй аргумент T_IND - то ясное дело, что вместо второго аргумента, в уровнение подставляются те 4 байта, которые мы берём из ячейки (T_IND % IDX_MOD)."
*/

void	ft_sti(t_process *process)
{
	char			codage[4];
	unsigned int	args[3];

	decipher_codage(codage, COUNT_ARGS(11), GET_CODAGE);
	if (check_valid_codage(OPCODE(10), codage) && ft_sti_check_args(args,
		codage, process, 2))
	{
		// ft_printf("%d\n", (short int)args[1] + (short int)args[2]);
		// ft_printf("%d\n", process->registries[args[2]]);
		// ft_printf("%d\n", codage[2]);
		// ft_printf("%d\n", codage[1]);
		set_map_value(process, process->registries[args[0]],
			((short int)(((codage[1] == REG_CODE) ? process->registries[args[1]] : args[1])
			+ ((codage[2] == REG_CODE) ? process->registries[args[2]]
			: args[2])) % IDX_MOD) % MEM_SIZE);
		fprintf(g_f, "ft_sti: in cycle ->%d<- process_position is ->%d<- __uints: arg0 %u arg1 %u__  __short arg0 %hd arg1 %hd__ carry %d\n", g_vm->cur_cycle, process->position, args[0], args[1], args[0], args[1], process->carry);
	}
	change_process_position(OPCODE(10), codage, process);
}
