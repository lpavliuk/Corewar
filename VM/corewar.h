/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 13:45:19 by tkiselev          #+#    #+#             */
/*   Updated: 2018/07/30 19:03:49 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <curses.h>
# define ABS(i)					i < 0 ? -i : i

# define T_REG_SIZE				1
# define T_DIR_SIZE				2
# define T_IND_SIZE				2

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

/*
** get/send this size of bytes
*/

// # define T_REG				1
// # define T_DIR				2
// # define T_IND				4

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

/*
** TO THE TABLE WE CAN REFER JUST WITH OPCODE OF COMMAND!!!
*/

# define NAME(i)				g_table[i - 1].name
# define COUNT_ARGS(i)			g_table[i - 1].args_count
# define ARG(i, j, k)			g_table[i - 1].args[j].arg[(int)k]
# define OPCODE(i) 				g_table[i].opcode
# define CODAGE(i) 				g_table[i - 1].codage
# define LABEL_SIZE(i)			g_table[i - 1].label_size
# define CYCLES_TO_PERFORM(i)	g_table[i - 1].cycles

# define MAX_TABLE 16

typedef struct
{
	char				arg[3];
}						t_arr;

typedef	struct			s_table
{
	char				*name;
	char				args_count;
	t_arr				args[3];
	char				opcode;
	char				codage : 1;
	char				label_size : 4;
	short				cycles;
}						t_table;

static t_table		g_table[16] = {
	{"live",	1,		{{{0, 1, 0}}, {{0, 0, 0}}, {{0, 0, 0}}},	1,	0,	4,	10		},
	{"ld",		2,		{{{0, 1, 1}}, {{1, 0, 0}}, {{0, 0, 0}}},	2,	1,	4,	5		},
	{"st",		2,		{{{1, 0, 0}}, {{1, 0, 1}}, {{0, 0, 0}}},	3,	1,	4,	5		},
	{"add",		3,		{{{1, 0, 0}}, {{1, 0, 0}}, {{1, 0, 0}}},	4,	1,	4,	10		},
	{"sub",		3,		{{{1, 0, 0}}, {{1, 0, 0}}, {{1, 0, 0}}},	5,	1,	4,	10		},
	{"and",		3,		{{{1, 1, 1}}, {{1, 1, 1}}, {{1, 0, 0}}},	6,	1,	4,	6		},
	{"or",		3,		{{{1, 1, 1}}, {{1, 1, 1}}, {{1, 0, 0}}},	7,	1,	4,	6		},
	{"xor",		3,		{{{1, 1, 1}}, {{1, 1, 1}}, {{1, 0, 0}}},	8,	1,	4,	6		},
	{"zjmp",	1,		{{{0, 1, 0}}, {{0, 0, 0}}, {{0, 0, 0}}},	9,	0,	2,	20		},
	{"ldi",		3,		{{{1, 1, 1}}, {{1, 1, 0}}, {{1, 0, 0}}},	10,	1,	2,	25		},
	{"sti",		3,		{{{1, 0, 0}}, {{1, 1, 1}}, {{1, 1, 0}}},	11,	1,	2,	25		},
	{"fork",	1,		{{{0, 1, 0}}, {{0, 0, 0}}, {{0, 0, 0}}},	12,	0,	2,	800		},
	{"lld",		2,		{{{0, 1, 1}}, {{1, 0, 0}}, {{0, 0, 0}}},	13,	1,	4,	10		},
	{"lldi",	3,		{{{1, 1, 1}}, {{1, 1, 0}}, {{1, 0, 0}}},	14,	1,	2,	50		},
	{"lfork",	1,		{{{0, 1, 0}}, {{0, 0, 0}}, {{0, 0, 0}}},	15,	1,	2,	1000	},
	{"aff",		1,		{{{1, 0, 0}}, {{0, 0, 0}}, {{0, 0, 0}}},	16,	1,	4,	2		}
};

/*
** exec - executable
*/

typedef struct		s_bot
{
	unsigned char 		player_counter;
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	unsigned char		*exec;
	unsigned int 		id;
	unsigned int		size;
	unsigned int		lives_whole;		/* Quantity of lives for the whole game. */
	unsigned int		lives_cur_period;	/* Quantity of lives for current period. */
	unsigned int		lives_last_period;	/* Quantity of lives for last period. */
	unsigned int		last_live;			/* Cycle on which this bot has executed shout his player/id/name. */
	struct s_bot		*next;
}						t_bot;

typedef struct			s_process
{
	unsigned int		position;	/* INDEX */
	unsigned char		carry : 1;
	unsigned char		live : 1;
	unsigned int		registries[REG_NUMBER + 1];
	unsigned char		opcode;
	unsigned int		cycles_to_perform;
	t_bot				*parent;
	struct s_process	*next;
}						t_process;

typedef struct			s_vm
{
	unsigned char		flag_visual : 1;
	unsigned char		flag_dump : 1;
	unsigned int		cycle_to_die;
	unsigned int		nbr_cycles;			/* Cycle on which we are going to dump memory. */
	unsigned int		cur_cycle;			/* Current cycle. */
	unsigned int		process_count;		/* Quantity of all processes on map. */
	char				count_players;
	unsigned int		port;
	char				*ip;
	char				*winner;
	t_process			*process;			/* All processes. */
	t_bot				*bot;
}						t_vm;

typedef struct			s_pixel
{
	unsigned char		counter;	/* How much iterations this pixel must be in bold */
	unsigned char		color : 3;	/* We have at our disposal 7 values */
	unsigned char		bold : 1;	/* We can put this bit in 1 and tell that this particular pixel will be in bold */
	unsigned char		live : 1;	/* Flag whether this pixel is live-pixel or not. */
	unsigned char		empty : 1;
}						t_pixel;

t_pixel					**g_pixels;
unsigned char			g_map[MEM_SIZE];

/*>>>>>>>>>> Visualisation <<<<<<<<<<*/

# define X_BEGIN	3
# define Y_BEGIN	2

# define KEY_Q		113
# define KEY_W		119
# define KEY_E		101
# define KEY_R		114
# define KEY_SPACE	32
# define RESIZE		410

# define ON			1
# define OFF		2

# define CURR_PERIOD 1
# define LAST_PERIOD 2

/* CURSOR */

# define CURSOR_X win->cursor_x
# define CURSOR_Y win->cursor_y

typedef struct
{
	WINDOW				*window;
	int					height;
	int					width;
	int					sidebar_pad;	/* Sidebar padding - quantity of columns to sidebar */
	int					cursor_y;
	int					cursor_x;
	short int			speed;			/* Speed of visualisation. */
	unsigned char		paused : 1;
}						t_win;

void					visualize(t_vm *vm);
void					ft_error(char *s);
void					usage(void);
unsigned int			get_arg(unsigned int i, char arg_size);
unsigned int			reverse_bytes(unsigned int data, char bytes);
char					get_arg_size(char opcode, char type);
char					get_arg_size(char opcode, char type);
char					*decipher_codage(unsigned char codage);
char					*pseudo_codage(char opcode);
void					get_args(t_vm *vm, int count, char **args);
void					get_server_info(t_vm *vm, char *args[], int argv,
						int *i);
t_process				*push_new_process(t_process **head, unsigned int
						*process_count, t_bot *parent, unsigned int position);
void					check_executable(t_bot *bot);
void					check_magic_header(int fd);
void					bot_parsing(int fd, t_bot *new);
t_bot					*push_new_bot(t_bot **head, unsigned int id);


/*
**	Process functions
*/

void	ft_live(t_process *process, t_vm *vm);

static void	(*func[16])(t_process *process, t_vm *vm) = {
	ft_live/*, ft_ld, ft_st, ft_add, ft_sub, ft_and, ft_or, ft_xor,
	ft_zjmp, ft_ldi, ft_sti, ft_fork_war, ft_lld, ft_lldi, ft_lfork, ft_aff}*/
}

#endif
