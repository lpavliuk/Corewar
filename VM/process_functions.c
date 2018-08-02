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

void	change_process_position(char opcode, char *codage, t_process *process)
{
	char	offset;
	char	i;

	i = 0;
	while (i < 3)
	{
		(codage[i] == IND_CODE) ? (offset += T_IND_SIZE) : 0;
		(codage[i] == REG_CODE) ? (offset += T_REG_SIZE) : 0;
		(codage[i] == DIR_CODE) ? (offset += LABEL_SIZE(opcode)) : 0;
		i++;
	}
	process->position = (process->position + offset + 1 + CODAGE(opcode))
		% MEM_SIZE;
}

void	ft_live(t_process *process, t_vm *vm)
{
	unsigned int	player_id;
	t_bot			*bot;

	process->live = 1;
	player_id = get_arg((process->position + 1) % MEM_SIZE,
		LABEL_SIZE(OPCODE(0)));
	bot = vm->bot;
	while (bot)
	{
		if (player_id == bot->id)
		{
			!vm->flag_visual ? ft_printf("Player %d (%s) is said to be alive\n",
				bot->player_counter, bot->name) : 1;
			bot->lives_cur_period++;
			bot->last_live = vm->cur_cycle;
		}
		bot = bot->next;
	}
	if (vm->flag_visual)
		g_pixels[process->position]->live = 50;
}

void	ft_ld(t_process *process, t_vm *vm)
{
	char			codage[4];
	unsigned int	arg2;
	unsigned int	result;

	decipher_codage(codage, COUNT_ARGS(2), (process->position + 1) % MEM_SIZE);
	if (check_valid_codage(OPCODE(1), codage)
	&& (arg2 = get_arg((process->position + ((codage[0] == IND_CODE) ? 2 : 4))
			% MEM_SIZE, T_REG_SIZE)) > 1 && arg2 < 17)
	{
		result = (codage[0] == IND_CODE) ? (get_arg((process->position
		+ (get_arg((process->position + 2) % MEM_SIZE, T_IND_SIZE) % IDX_MOD))
		% MEM_SIZE, T_IND_READ)) : (get_arg((process->position + 2) % MEM_SIZE,
			T_DIR_SIZE));
		process->registries[arg2] = result;
		process->carry = (result) ? 0 : 1;
	}
	change_process_position(OPCODE(1), codage, process);
}

/*
**	set_map_value() - print 4 bytes on the g_map and set appropriate values in g_pixels array
*/

void	set_map_value(t_process *process, unsigned int val,
		unsigned int new_pstn, t_vm *vm)
{
	int		j;

	j = 0;
	while (j < 4)
	{
		g_map[(process->position + new_pstn + j) % MEM_SIZE] =
			((unsigned char *)&val)[j];
		if (vm->flag_visual)
		{
			g_pixels[(process->position + new_pstn + j) % MEM_SIZE]->counter
				= 50;
			g_pixels[(process->position + new_pstn + j) % MEM_SIZE]->color
				= process->parent->player_counter;
			g_pixels[(process->position + new_pstn + j) % MEM_SIZE]->bold = 1;
		}
		j++;
	}
}

void	ft_st(t_process *process, t_vm *vm)
{
	char			codage[4];
	unsigned int	position_arg2;
	unsigned int	result;

	decipher_codage(codage, COUNT_ARGS(3), (process->position + 1) % MEM_SIZE);
	if (check_valid_codage(OPCODE(2), codage) && (result = get_arg(
		(process->position + 2) % MEM_SIZE, T_REG_SIZE) > 0) && result < 17)
	{
		position_arg2 = get_arg((process->position + 3) % MEM_SIZE, ((codage[1]
			== IND_CODE) ? T_IND_SIZE : T_REG_SIZE));
		if (codage[1] == IND_CODE)
		{
			position_arg2 %= IDX_MOD;
			set_map_value(process, result, position_arg2, vm);
		}
		else if (position_arg2 > 0 && position_arg2 <= REG_NUMBER)
			process->registries[position_arg2] = result;
	}
	change_process_position(OPCODE(2), codage, process);
}

void	ft_add(t_process *process, t_vm *vm)
{
	char	i;
	char	codage[4];
	char	args[3];

	i = 0;
	decipher_codage(codage, COUNT_ARGS(4), (process->position + 1) % MEM_SIZE);
	if (check_valid_codage(OPCODE(3), codage))
	{
		while(i < 3)
		{
			args[i] = get_arg((process->position + (i + T_REG_SIZE)) % MEM_SIZE,
					T_REG_SIZE);
			if (!(args[i] > 0 && args[i] < 17))
				break ;
			i++;
		}
		if (i == 3)
		{
			process->registries[args[2]] = process->registries[args[0]]
			+ process->registries[args[1]];
			process->carry = (process->registries[args[2]]) ? 0 : 1;
		}
	}
	change_process_position(OPCODE(3), codage, process);
}

void	ft_sub(t_process *process, t_vm *vm)
{
	char	i;
	char	codage[4];
	char	args[3];

	i = 0;
	decipher_codage(codage, COUNT_ARGS(5), (process->position + 1) % MEM_SIZE);
	if (check_valid_codage(OPCODE(4), codage))
	{
		while(i < 3)
		{
			args[i] = get_arg((process->position + (i + T_REG_SIZE)) % MEM_SIZE,
					T_REG_SIZE);
			if (!(args[i] > 0 && args[i] < 17))
				break ;
			i++;
		}
		if (i == 3)
		{
			process->registries[args[2]] = process->registries[args[0]]
			- process->registries[args[1]];
			process->carry = (process->registries[args[2]]) ? 0 : 1;
		}
	}
	change_process_position(OPCODE(4), codage, process);
}

/* WITH IDX_MOD OR NOT??????? */

int		ft_and_or_xor_args(unsigned int *args, char *codage,
	t_process *process, char offset)
{
	char	i;

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
			+ (offset - LABEL_SIZE(OPCODE(6)))) % MEM_SIZE, T_DIR_SIZE);
		i++;
	}
	return (1);
}

void	ft_and(t_process *process, t_vm *vm)
{
	char	codage[4];
	char	args[3];

	decipher_codage(codage, COUNT_ARGS(6), (process->position + 1) % MEM_SIZE);
	if (check_valid_codage(OPCODE(5), codage) && ft_and_or_xor_args(args,
		codage, process, 2))
	{
		process->registries[args[2]] = ((codage[0] == REG_CODE) ?
			process->registries[args[0]] : args[0]) & ((codage[1] == REG_CODE) ?
			process->registries[args[1]] : args[1]);
		(process->registries[args[2]]) ? (process->carry = 0) : 1;
	}
	change_process_position(OPCODE(4), codage, process);
}

void	ft_or(t_process *process, t_vm *vm)
{
	char	codage[4];
	char	args[3];

	decipher_codage(codage, COUNT_ARGS(6), (process->position + 1) % MEM_SIZE);
	if (check_valid_codage(OPCODE(5), codage) && ft_and_or_xor_args(args,
		codage, process, 2))
	{
		process->registries[args[2]] = ((codage[0] == REG_CODE) ?
			process->registries[args[0]] : args[0]) | ((codage[1] == REG_CODE) ?
			process->registries[args[1]] : args[1]);
		(process->registries[args[2]]) ? (process->carry = 0) : 1;
	}
	change_process_position(OPCODE(4), codage, process);
}

void	ft_xor(t_process *process, t_vm *vm)
{
	char	codage[4];
	char	args[3];

	decipher_codage(codage, COUNT_ARGS(6), (process->position + 1) % MEM_SIZE);
	if (check_valid_codage(OPCODE(5), codage) && ft_and_or_xor_args(args,
		codage, process, 2))
	{
		process->registries[args[2]] = ((codage[0] == REG_CODE) ?
			process->registries[args[0]] : args[0]) ^ ((codage[1] == REG_CODE) ?
			process->registries[args[1]] : args[1]);
		(process->registries[args[2]]) ? (process->carry = 0) : 1;
	}
	change_process_position(OPCODE(4), codage, process);
}

void	ft_zjmp(t_process *process, t_vm *vm)
{
	if (process->carry)
		process->position = get_arg(((process->position + 1) % IDX_MOD),
			T_DIR_SIZE);
	else
		process->position = (process->position + 1 + T_DIR_SIZE) % MEM_SIZE;
}

int		ft_ldi_lldi_check_args(unsigned int *args, char *codage,
	t_process *process, char offset)
{
	char	i;

	i = 0;
	while (i < 3)
	{
		if (codage[i] == IND_CODE && (offset += T_IND_SIZE))
			args[i] = get_arg((process->position + (get_arg((process->position
			+ 2) % MEM_SIZE, T_IND_SIZE) % IDX_MOD)) % MEM_SIZE, T_IND_READ);
		else if (codage[i] == REG_CODE)
		{
			args[i] = get_arg((process->position + offset)
				% MEM_SIZE, T_REG_SIZE);
			offset += T_REG_SIZE;
			if (args[i] < 1 || args[i] > 16)
				return (0);
		}
		else if (codage[i] == DIR_CODE && (offset += LABEL_SIZE(OPCODE(9)))) /* LABEL_SIZE(OPCODE(9)) == LABEL_SIZE(OPCODE(13))*/
			args[i] = get_arg((process->position
			+ (offset - LABEL_SIZE(OPCODE(9)))) % MEM_SIZE, T_DIR_SIZE);
		i++;
	}
	return (1);
}

void	ft_ldi(t_process *process, t_vm *vm)
{
	char			codage[4];
	unsigned int	args[3];
	unsigned int	result;

	decipher_codage(codage, COUNT_ARGS(10), (process->position + 1) % MEM_SIZE);
	if (check_valid_codage(OPCODE(9), codage) && ft_ldi_lldi_check_args(args,
		codage, process, 2))
	{
		result = get_arg((process->position + ((args[0] + args[1]) % IDX_MOD))
			% MEM_SIZE, T_IND_READ);
		process->registries[args[2]] = result;
	}
	change_process_position(OPCODE(9), codage, process);
}

int		ft_sti_check_args(unsigned int *args, char *codage, t_process *process,
		char offset)
{
	char	i;

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

void	ft_sti(t_process *process, t_vm *vm)
{
	char			codage[4];
	unsigned int	args[3];

	decipher_codage(codage, COUNT_ARGS(11), (process->position + 1) % MEM_SIZE);
	if (check_valid_codage(OPCODE(10), codage) && ft_sti_check_args(args,
		codage, process, 2))
	{
		set_map_value(process, process->registries[args[0]],
			((((codage[1] == REG_CODE) ? process->registries[args[1]] : args[1])
			+ ((codage[2] == REG_CODE) ? process->registries[args[2]]
			: args[2])) % IDX_MOD) % MEM_SIZE, vm);
	}
	change_process_position(OPCODE(10), codage, process);
}

void	copy_new_process(t_process **head, t_process *process, t_vm *vm,
		unsigned int position)
{
	t_process	*new;
	char		i;

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
	new->carry = process->carry;
	new->live = process->live;
	new->opcode = process->opcode;
	new->codage = process->codage;
	new->cycles_to_perform = 0;
	new->next = NULL;
	if (*head)
		new->next = *head;
	*head = new;
	(vm->process_count)++;
}

void	ft_fork(t_process *process, t_vm *vm)
{
	unsigned int new_position;

	new_position = ((get_arg((process->position + 1) % MEM_SIZE, T_DIR_SIZE)
		% IDX_MOD) + process->position) % MEM_SIZE;
	copy_new_process(&(vm->process), process, vm, new_position);
	process->position = (process->position + T_DIR_SIZE + 1) % MEM_SIZE;
}

void	ft_lld(t_process *process, t_vm *vm)
{
	char			codage[4];
	unsigned int	arg2;
	unsigned int	result;

	decipher_codage(codage, COUNT_ARGS(13), (process->position + 1) % MEM_SIZE);
	if (check_valid_codage(OPCODE(12), codage)
	&& (arg2 = get_arg((process->position + ((codage[0] == IND_CODE) ? 2 : 4))
			% MEM_SIZE, T_REG_SIZE)) > 1 && arg2 < 17)
	{
		result = (codage[0] == IND_CODE) ? (get_arg((process->position
		+ get_arg((process->position + 2) % MEM_SIZE, T_IND_SIZE))
		% MEM_SIZE, T_IND_READ)) : (get_arg((process->position + 2) % MEM_SIZE,
			T_DIR_SIZE));
		process->registries[arg2] = result;
		process->carry = (result) ? 0 : 1;
	}
	change_process_position(OPCODE(12), codage, process);
}

void	ft_lldi(t_process *process, t_vm *vm)
{
	char			codage[4];
	unsigned int	args[3];
	unsigned int	result;

	decipher_codage(codage, COUNT_ARGS(14), (process->position + 1) % MEM_SIZE);
	if (check_valid_codage(OPCODE(13), codage) && ft_ldi_check_args(args,
		codage, process, 2))
	{
		result = get_arg((process->position + (args[0] + args[1]))
			% MEM_SIZE, T_IND_READ);
		process->registries[args[2]] = result;
		process->carry = (result) ? 0 : 1;
	}
	change_process_position(OPCODE(13), codage, process);
}

void	ft_lfork(t_process *process, t_vm *vm)
{
	unsigned int new_position;

	new_position = (get_arg((process->position + 1) % MEM_SIZE, T_DIR_SIZE)
		+ process->position) % MEM_SIZE;
	copy_new_process(&(vm->process), process, vm, new_position);
	process->position = (process->position + T_DIR_SIZE + 1) % MEM_SIZE;
}

/* WTF-FUNCTION */

void	ft_aff(t_process *process, t_vm *vm)
{
	char			codage[4];
	unsigned int	reg_num;

	decipher_codage(codage, COUNT_ARGS(16), (process->position + 1) % MEM_SIZE);
	if (codage[0] == REG_CODE)
	{
		reg_num = get_arg((process->position + 1) % MEM_SIZE, T_REG_SIZE);
		if (reg_num > 0 && reg_num < 17 && !vm->flag_visual)
			ft_printf("%c", process->registries[reg_num]);
	}
	change_process_position(OPCODE(15), codage, process);
}
