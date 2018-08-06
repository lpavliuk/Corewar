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
		unsigned int new_pstn)
{
	int		j;

	j = 0;
	while (j < 4)
	{
		g_map[(new_pstn + j) % MEM_SIZE] = ((unsigned char *)&val)[3 - j];
		if (g_vm->flag_visual)
		{
			g_pixels[(new_pstn + j) % MEM_SIZE]->counter = 50;
			g_pixels[(new_pstn + j) % MEM_SIZE]->color
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

int		ft_sti_check_args(unsigned int *uargs, short int *sargs, char *codage,
	t_process *process)
{
	int		i;
	char	offset;

	i = 0;
	offset = 2;
	while (i < 3)
	{
		if (codage[i] == REG_CODE)
		{
			uargs[i] = get_arg((process->position + offset) % MEM_SIZE,
				T_REG_SIZE);
			offset += T_REG_SIZE;
			if (uargs[i] < 1 || uargs[i] > 16)
				return (0);
		}
		else if (codage[i] == IND_CODE && (offset += T_IND_SIZE))
			uargs[i] = get_arg((process->position + (get_arg((process->position
			+ (offset - T_IND_SIZE)) % MEM_SIZE, T_IND_SIZE) % IDX_MOD))
			% MEM_SIZE, T_IND_READ);
		else if (codage[i] == DIR_CODE && (offset += T_DIR_SIZE))
			sargs[i] = get_arg((process->position
				+ (offset - T_DIR_SIZE)) % MEM_SIZE, T_DIR_SIZE);
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
	short int		sargs[3];
	unsigned int	uargs[3];
	int				ch_pos;

	decipher_codage(codage, COUNT_ARGS(11), GET_CODAGE);
	if (check_valid_codage(OPCODE(10), codage) && ft_sti_check_args(uargs,
		sargs, codage, process))
	{
		if (codage[1] == REG_CODE)
			ch_pos = process->registries[uargs[1]];
		else if (codage[1] == IND_CODE)
			ch_pos = uargs[1];
		else if (codage[1] == DIR_CODE)
			ch_pos = sargs[1];
		if (codage[2] == REG_CODE)
			ch_pos += process->registries[uargs[2]];
		else if (codage[2] == DIR_CODE)
			ch_pos += sargs[2];
		ft_printf("STI %d reg == %d cycle %d\n", process->registries[uargs[0]], uargs[0], g_vm->cur_cycle);
		set_map_value(process, process->registries[uargs[0]],
			(process->position + (ch_pos % IDX_MOD)) % MEM_SIZE);
	}
	change_process_position(OPCODE(10), codage, process);
}
