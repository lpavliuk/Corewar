/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 13:45:19 by tkiselev          #+#    #+#             */
/*   Updated: 2018/07/11 13:45:23 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../libft/libft.h"
# include <fcntl.h>

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				0
# define DIR_CODE				1
# define IND_CODE				2

# define MAX_ARGS_NUMBER			4
# define MAX_PLAYERS				4
# define MEM_SIZE				(4 * 1024)
# define IDX_MOD					(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR				'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD			".name"
# define COMMENT_CMD		".comment"

# define REG_NUMBER				16



// # define CYCLE_TO_DIE			1536
// # define CYCLE_DELTA				50
// # define NBR_LIVE				21
// # define MAX_CHECKS				10

// # define T_REG					1
// # define T_DIR					2
// # define T_IND					4
// # define T_LAB					8



# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

# define ERR_BRACKET "not-closed bracket."
# define ERR_NAME "second name."
# define ERR_FILE "Can't read source file "

# define GET_NAME 1
# define GET_COMMENT 2


# define NAME(i) g_table[i].name
# define COUNT_ARG(i) g_table[i].args_count
# define ARG1(i, num) g_table[i].arg1[num]
# define ARG2(i, num) g_table[i].arg2[num]
# define ARG3(i, num) g_table[i].arg3[num]
# define OPCODE(i) g_table[i].opcode
# define CYCLES(i) g_table[i].cycles
# define CODAGE(i) g_table[i].codage
# define CARRY(i) g_table[i].carry
# define LABEL_SIZE(i) g_table[i].label_size
# define HEX(i) g_table[i].hex

# define MAX_TABLE 16


typedef	struct		s_table
{
	char			*name;
	char			args_count;
	char			arg1[3];
	char			arg2[3];
	char			arg3[3];
	char			opcode;
	short			cycles;
	char			codage : 1;
	char			carry : 1;
	char			label_size : 4;
	char			hex[3];
}					t_table;

static t_table		g_table[16] = {
	{"live", 1, {0, 1, 0}, {0, 0, 0}, {0, 0, 0}, 1, 10, 0, 0, 4, "01"},
	{"ld", 2, {0, 1, 1}, {1, 0, 0}, {0, 0, 0}, 2, 5, 1, 0, 4, "02"},
	{"st", 2, {1, 0, 0}, {1, 0, 1}, {0, 0, 0}, 3, 5, 1, 0, 4, "03"},
	{"add", 3, {1, 0, 0}, {1, 0, 0}, {1, 0, 0}, 4, 10, 1, 0, 4, "04"},
	{"sub", 3, {1, 0, 0}, {1, 0, 0}, {1, 0, 0}, 5, 10, 1, 0, 4, "05"},
	{"and", 3, {1, 1, 1}, {1, 1, 1}, {1, 0, 0}, 6, 6, 1, 0, 4, "06"},
	{"or", 3, {1, 1, 1}, {1, 1, 1}, {1, 0, 0}, 7, 6, 1, 0, 4, "07"},
	{"xor", 3, {1, 1, 1}, {1, 1, 1}, {1, 0, 0}, 8, 6, 1, 0, 4, "08"},
	{"zjmp", 1, {0, 1, 0}, {0, 0, 0}, {0, 0, 0}, 9, 20, 0, 0, 2, "09"},
	{"ldi", 3, {1, 1, 1}, {1, 1, 0}, {1, 0, 0}, 10, 25, 1, 0, 2, "0a"},
	{"sti", 3, {1, 0, 0}, {1, 1, 1}, {1, 1, 0}, 11, 25, 1, 0, 2, "0b"},
	{"fork", 1, {0, 1, 0}, {0, 0, 0}, {0, 0, 0}, 12, 800, 0, 0, 2, "0c"},
	{"lld", 2, {0, 1, 1}, {1, 0, 0}, {0, 0, 0}, 13, 10, 1, 0, 4, "0d"},
	{"lldi", 3, {1, 1, 1}, {1, 1, 0}, {1, 0, 0}, 14, 50, 1, 0, 2, "0e"},
	{"lfork", 1, {0, 1, 0}, {0, 0, 0}, {0, 0, 0}, 15, 1000, 0, 0, 2, "0f"},
	{"aff", 1, {1, 0, 0}, {0, 0, 0}, {0, 0, 0}, 16, 2, 1, 0, 4, "10"}
};

/*
** opcode in t_command are equal to enum(operation_name) - 1;!!!
*/

typedef struct		s_command
{
	unsigned char		codage;
	char				bytes;
	char				bytes_before;
	char				opcode;
	char				*label;
	unsigned int		arg1;
	char 				size_arg1;
	unsigned int		arg2;
	char 				size_arg2;
	unsigned int		arg3;
	char 				size_arg3;
	struct s_command	*next;
}					t_command;

typedef struct		s_asm
{
	unsigned int	prog_size;
	unsigned int	magic;
	char			*line;
	char			prog_name[PROG_NAME_LENGTH + 1];
	char			*file_name;
	char			flag_a : 1;
	char			comment[COMMENT_LENGTH + 1];
	int				new_fd;
	int				fd;
	t_command		*command;
}					t_asm;

void				ft_error(char *str);

#endif
