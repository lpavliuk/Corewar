#include "asm.h"
#include <stdio.h>

//DELETE THIS SHIT!!!
void	prohodochka(t_asm *asmb)
{
	t_command *command;

	command = asmb->command;
	while (command)
	{
		printf("command->name = %s\n", command->name);

		while (command->labels)
		{
			printf("label = %s\n", (char *)command->labels->content);
			command->labels = command->labels->next;
		}
		
		while (command->args)
		{
			printf("arg = %d\n", command->args->num_value);
			command->args = command->args->next;
		}
		
		printf("codage = %d\n", command->codage);
		printf("bytes_before = %d\n", command->bb);
		printf("bytes = %d\n", command->bytes);
		command = command->next;
	}
	printf("program size = %d\n", asmb->prog_size);
}

void	ft_error(char *str)
{
	ft_printf("%s\n", str);
	exit(0);
}

void	skip_shit(char *str, int *j, char *symbols)
{
	while (str[*j] && ft_strchr(symbols, str[*j]))
		(*j)++;
}

t_asm			*init_asmb(void)
{
	t_asm		*s;

	if (!(s = (t_asm*)malloc(sizeof(t_asm))))
		ft_error("Error [init_asmb()]: memory was not allocated");
	ft_bzero(s->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(s->comment, COMMENT_LENGTH + 1);
	s->file_name = NULL;
	s->command = NULL;
	s->line = NULL;
	s->flag_a = 0;
	s->prog_size = 0;
	s->new_fd = 0;
	s->fd = 0;
	s->last_line_size = 0;
	s->magic = COREWAR_EXEC_MAGIC;
	return (s);
}

/*
** 3 functions for checking if it's line is
** bot_name_line, bot_comment_line or comment_line
*/

char		is_bot_name(char *s)
{
	if (!s)
		return (0);
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	if (ft_strncmp(s, NAME_CMD, ft_strlen(NAME_CMD)) == 0)
		return (1);
	return (0);
}

char		is_bot_comment(char *s)
{
	if (!s)
		return (0);
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	if (ft_strncmp(s, COMMENT_CMD, ft_strlen(COMMENT_CMD)) == 0)
		return (1);
	return (0);
}

char		is_comment(char *s)
{
	if (!s)
		return (0);
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	return ((*s == ';' || *s == '#' || *s == '\0') ? 1 : 0);
}

/*
** this function copies string to dest after command and between brackets.
*/

void	copy_to_dst(t_asm *asmb, char *dest, int size, int *j)
{
	int		i;

	i = 0;
	while (asmb->line)
	{
		while (i < size && asmb->line[*j] && asmb->line[*j] != '\"')
			dest[i++] = asmb->line[(*j)++];
		if (asmb->line[*j] == '\"')
			return ;
		else if (i < size) // it means that the last character in asmb->line is '\0'.
			dest[i++] = '\n';
		else
			ft_error("Error");
		*j = 0;
		ft_strdel(&asmb->line);
		get_next_line(asmb->fd, &asmb->line);
	}
}

/*
** this function gets string after command.
*/

void		get_str(t_asm *asmb, char flag)
{
	int		j;
	int		size;
	char	*dest;

	j = ft_strstr(asmb->line, ((flag == GET_NAME) ? NAME_CMD : COMMENT_CMD)) -
		asmb->line + ft_strlen(((flag == GET_NAME) ? NAME_CMD : COMMENT_CMD));
	size = (flag == GET_NAME) ? PROG_NAME_LENGTH : COMMENT_LENGTH;
	dest = (flag == GET_NAME) ? asmb->prog_name : asmb->comment;
	while (asmb->line[j] && (asmb->line[j] == ' ' || asmb->line[j] == '\t'))
		j++;
	(asmb->line[j] != '\"') ? ft_error("Error") : j++;
	copy_to_dst(asmb, dest, size, &j);
	(!asmb->line || asmb->line[j] != '\"') ? ft_error("Error") : j++;
	while (asmb->line[j] && (asmb->line[j] == ' ' || asmb->line[j] == '\t'))
		j++;
	if (asmb->line[j] != ';' && asmb->line[j] != '#' && asmb->line[j] != '\0') // \0 || \n!!!!!!!!!!
		ft_error("Error");
}

/*
** function that gets prog_name and comment, and also checks if strings are valid or not.
*/

void	get_header(t_asm *asmb)
{
	char	flag; // 1 bit is for name, and 2 bit - for comment.

	flag = 0;
	while (get_next_line(asmb->fd, &asmb->line) > 0)
	{
		if (is_bot_name(asmb->line))
		{
			(flag & 1) ? ft_error("Error") : (flag = flag | 1);
			get_str(asmb, GET_NAME); // GET_NAME means that we are going to get name.
		}
		else if (is_bot_comment(asmb->line))
		{
			(flag & 2) ? ft_error("Error") : (flag = flag | 2);
			get_str(asmb, GET_COMMENT); // GET_COMMENT means that we are going to get name.
		}
		else if (!is_comment(asmb->line))
			ft_error("Error");
		ft_strdel(&asmb->line);
		if (flag == 3)
			break ;
	}
	(flag != 3) ? ft_error("Error\n") : 0;
}

/*
** functions that get commands.
*/

char	check_last_line(t_asm *asmb)
{
	char	s[asmb->last_line_size + 1];
	int		i;

	i = 0;
	ft_bzero(s, asmb->last_line_size + 1);
	lseek(asmb->fd, -asmb->last_line_size, SEEK_CUR);
	read(asmb->fd, &s, asmb->last_line_size);
	skip_shit(s, &i, " \t");
	if (s[i] != '\0' && s[i] != ';' && s[i] != '#')
	{
		i = ft_strlen(s) - 1;
		if (i >= 0 && s[i] == '\n')
			return (1);
		else
			return (0);
	}
	return (1);
}

int		index_of(char *needle, int len)
{
	int i;

	i = 0;
	while (i < MAX_TABLE)
	{
		if (ft_strnequ(NAME(i + 1), needle, len)) // + 1 here because to table we refer just with opcode.
			return (i);
		i++;
	}
	return (-1);
}

char	str_has(char *str, char flag)
{
	int i;

	if (!str)
		return (0);
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	if (flag == LABEL)
	{
		while (*str && *str != ':')
			if (!ft_strchr(LABEL_CHARS, *str++))
				return (0);
		return ((*str == ':') ? 1 : 0);
	}
	else if (flag == COMMAND)
	{
		(str_has(str, LABEL)) ? (str = ft_strchr(str, ':') + 1) : 0;
		while (*str && (*str == ' ' || *str == '\t'))
			str++;
		i = 0;
		while (str[i] && str[i] != ' ' && str[i] != '\t')
			i++;
		return ((i > 0 && index_of(str, i) != -1) ? 1 : 0);
	}
	return (0);
}

t_command	*push_new_command(t_command **head)
{
	t_command	*new;
	t_command	*tmp;

	tmp = *head;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!(new = (t_command*)malloc(sizeof(t_command))))
		ft_error("Error");
	new->next = NULL;
	new->args = NULL;
	new->labels = NULL;
	new->opcode = 0;
	new->bb = 0;
	new->bytes = 0;
	new->codage = 0;
	new->name = NULL;
	if (!*head)
		*head = new;
	else
		tmp->next = new;
	return (new);
}

char	*my_strsub(char *src, int start, int end)
{
	char	*s;
	int		i;
	int		size;

	size = end - start;
	if (!(s = (char *)malloc(size + 1)))
		ft_error("Error");
	ft_bzero(s, size + 1);
	i = 0;
	while (i < size)
	{
		s[i] = src[start + i];
		i++;
	}
	return (s);
}

void	get_label(t_list **labels, char *s, int *j)
{
	int tmp;
	char	*tmp_s;

	tmp = *j;
	while (s[*j] && s[*j] != ':')
		(*j)++;
	tmp_s = my_strsub(s, tmp, *j);
	ft_list_pushback(labels, tmp_s);
	free(tmp_s);
	(*j)++;
}

void	get_labels(t_asm *asmb, t_command *new, int *j)
{
	char	*s;

	while (asmb->line)
	{
		asmb->last_line_size = ft_strlen(asmb->line);
		s = asmb->line;
		skip_shit(s, j, " \t");
		if (str_has(s, LABEL))
			get_label(&new->labels, s, j);
		skip_shit(s, j, " \t");
		if (s[*j] != '\0' && !is_comment(s + *j))
			return ;
		*j = 0;
		ft_strdel(&asmb->line);
		get_next_line(asmb->fd, &asmb->line);
	}
}

void	get_command(t_asm *asmb, t_command *new, int *j) // gets command_name and opcode.
{
	char	*s;
	int		tmp;

	s = asmb->line;
	tmp = *j;
	while (s[*j] && s[*j] != '-' && s[*j] != '%' && s[*j] != ' ' &&
		s[*j] != '\t' && (s[*j] < '0' || s[*j] > '9'))
		(*j)++;
	if (s[*j] != ' ' && s[*j] != '\t' && s[*j] != '%' && s[*j] != '-')
		ft_error("Error");
	new->name = my_strsub(s, tmp, *j);
	new->opcode = index_of(new->name, ft_strlen(new->name)) + 1;
	(new->opcode == -1) ? ft_error("Error") : 0;
}

/*
** functions which gets arguments after cmd.
*/

void	array_map(char **arr, char* (*f)(const char *))
{
	char	*tmp;
	int		i;

	i = 0;
	while (arr[i])
	{
		tmp = (*f)(arr[i]);
		free(arr[i]);
		arr[i] = tmp;
		i++;
	}
}

t_arg	*push_new_arg(t_arg **args)
{
	t_arg	*new;
	t_arg	*tmp;

	if (!(new = (t_arg *)malloc(sizeof(t_arg))))
		ft_error("Error");
	new->str_value = NULL;
	new->num_value = 0;
	new->arg_size = 0;
	new->type = 0;
	new->flag = 0;
	new->next = NULL;
	tmp = *args;
	while (tmp && tmp->next)
		tmp = tmp->next;
	(!tmp) ? (*args = new) : (tmp->next = new);
	return (new);
}

char	is_treg(char *str)
{
	int	tmp;

	if (*str == 'r')
	{
		str++;
		if (!ft_is_uint(str) || *str == '-' || *str == '+')
			return (0);
		tmp = ft_atoi(str);
		if (tmp >= 0 && tmp <= REG_NUMBER)
			return (1);
	}
	return (0);
}

char	is_tdir(char *str)
{
	if (*str == '%')
	{
		str++;
		if (*str == ':')
		{
			str++;
			if (!ft_strchr(str, ':'))
				return (1);
		}
		else if (*str)
		{
			(*str == '-') ? str++ : 0;
			while (ft_isdigit(*str))
				str++;
			if (*str == '\0')
				return (1);
		}
	}
	return (0);
}

char	is_tind(char *str)
{
	if (*str == ':')
	{
		str++;
		if (!ft_strchr(str, ':'))
			return (1);
	}
	else if (*str)
	{
		(*str == '-') ? str++ : 0;
		while (ft_isdigit(*str))
			str++;
		if (*str == '\0')
			return (1);
	}
	return (0);
}

char	get_type(char *str)
{
	if (is_treg(str))
		return (T_REG);
	else if (is_tdir(str))
		return (T_DIR);
	else if (is_tind(str))
		return (T_IND);
	return (UNDEFINED_TYPE);
}

void	*get_data(char type, char *str, char *flag)
{
	unsigned int	*num_val;

	if (type == T_REG)
	{
		*flag = UINT_VAL;
		num_val = (unsigned int *)malloc(sizeof(unsigned int));
		*num_val = ft_atoi(str + 1); // because these strings has 'r' at the beginning.
		return ((void*)num_val);
	}
	else
	{
		(*str == '%') ? str++ : 0;
		if (*str == ':')
		{
			*flag = STRING_VAL;
			return ((void*)my_strsub(str + 1, 0, ft_strlen(str) - 1)); // because at the beginning we have ':'.
		}
		else
		{
			*flag = UINT_VAL;
			num_val = (unsigned int *)malloc(sizeof(unsigned int));
			*num_val = ft_atoi(str);
			return ((void*)num_val);
		}
	}
}

char	get_arg_size(char opcode, char type)
{
	if (type == T_REG)
		return (T_REG_SIZE);
	else if (type == T_IND)
		return (T_IND_SIZE);
	else
	{
		if (LABEL_SIZE(opcode) == 4)
			return (4);
		else
			return (T_DIR_SIZE);
	}
}

void	add_argument(t_command *command, char type, void *data, char flag)
{
	t_arg	*new;

	new = push_new_arg(&command->args);
	if (flag == STRING_VAL)
	{
		new->str_value = (char *)data;
		new->flag = 1; // we must return to this variable because it's just a pointer to a label which we cannot have on this stage.
	}
	else if (flag == UINT_VAL)
	{
		new->num_value = ((int *)data)[0];
		free(data);
	}
	new->type = type;
	new->arg_size = get_arg_size(command->opcode, type);
}

void	foreach_arg(char **arr, t_command *command)
{
	int		i;
	char	type;
	char	flag;

	i = 0;
	while (arr[i])
	{
		flag = 0;
		type = get_type(arr[i]);
		if (type == UNDEFINED_TYPE)
			ft_error("Error");
		add_argument(command, type, get_data(type, arr[i], &flag), flag); // we pass flag just in order to determine if this argument is INT or CHAR *.
		i++;
	}
}


/*
** SEGFAULT CAN BE HERE!!!!!!!!!!!!!!!!!!!!!!
*/

void	check_arguments(t_command *command)
{
	t_arg	*arg;
	int		len;

	len = 0;
	arg = command->args;
	while (arg)
	{
		(len > 3) ? ft_error("Error") : 0; 							// for counting quantity of arguments.
		(!ARG(command->opcode, len, arg->type)) ? ft_error("Error") : 0;
		len++;
		arg = arg->next;
	}
	(COUNT_ARGS(command->opcode) != len) ? ft_error("Error") : 0;
}

void	get_arguments(t_asm *asmb, t_command *new, int j)
{
	char	*tmp;
	char	**arr;
	int		t1;
	int		t2;
	int		i;

	t1 = ((int)ft_strchr(asmb->line, ';'));
	t2 = ((int)ft_strchr(asmb->line, '#'));
	if (t1 != 0 && t2 != 0) 														// if string contains both, we choose the one that occurs earlier.
		tmp = my_strsub(asmb->line, j, ((t1 < t2) ? t1 : t2) - (int)asmb->line);
	else if ((t1 == 0) ^ (t2 == 0)) 												// if string contains one of these.
		tmp = my_strsub(asmb->line, j, ((t1 == 0) ? t2 : t1) - (int)asmb->line);
	else
		tmp = my_strsub(asmb->line, j, ft_strlen(asmb->line));
	if (!(arr = ft_strsplit(tmp, SEPARATOR_CHAR)))
		ft_error("Error");
	array_map(arr, ft_strtrim);
	foreach_arg(arr, new);
	free(tmp);
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	check_arguments(new);
}

void	get_lca(t_asm *asmb) // lca means label + command + arguments
{
	t_command	*new;
	int			j;

	j = 0;
	new = push_new_command(&asmb->command);
	get_labels(asmb, new, &j);
	if (str_has(asmb->line, COMMAND))
	{
		get_command(asmb, new, &j);
		get_arguments(asmb, new, j);
	}
	else if (asmb->line && !is_comment(asmb->line + j))
		ft_error("Error");
}

void	get_codage(t_command *command)
{
	t_arg	*arg;
	unsigned char	n;
	char	len;

	if (!CODAGE(command->opcode))
		return ;
	n = 0;
	len = 4;
	arg = command->args;
	while (arg)
	{
		(n) ? (n <<= 2) : 0;
		(arg->type == T_REG) ? (n |= 1) : 0;
		(arg->type == T_DIR) ? (n |= 2) : 0;
		(arg->type == T_IND) ? (n |= 3) : 0;
		len--;
		arg = arg->next;
	}
	n <<= (len * 2);
	command->codage = n;
}

void	get_bytes(t_command *command)
{
	t_arg	*arg;

	if (command->opcode) // because if opcode == 0, command doesn't exist.
	{
		command->bytes++;
		arg = command->args;
		(CODAGE(command->opcode)) ? command->bytes++ : 0;
		while (arg)
		{
			command->bytes += arg->arg_size;
			arg = arg->next;
		}
	}
}

void	get_val_from_pointer(t_command *head, t_command *command, t_arg *arg)
{
	t_list	*label;

	while (head)
	{
		label = head->labels;
		while (label)
		{
			if (ft_strequ(label->content, arg->str_value))
			{
				arg->num_value = head->bb - command->bb;
				ft_strdel(&arg->str_value);
				arg->flag = 0;
				return ;
			}
			label = label->next;
		}
		head = head->next;
	}
	ft_error("Error"); // if there are not such label.
}

void			compute_tdirs(t_command *command)
{
	t_command	*tmp;
	t_arg		*arg;

	tmp = command;
	while (tmp)
	{
		arg = tmp->args;
		while (arg)
		{
			if (arg->flag)
				get_val_from_pointer(command, tmp, arg);
			arg = arg->next;
		}
		tmp = tmp->next;
	}
}

unsigned int	compute_variables(t_command *command)
{
	t_command	*tmp;

	tmp = command;
	while (command)
	{
		get_codage(command);
		get_bytes(command);
		if (command->next)
		{
			command->next->bb = command->bb + command->bytes;
			command = command->next;
		}
		else
			break ;
	}
	compute_tdirs(tmp);
	return (command->bb + command->bytes);
}

void	get_commands(t_asm *asmb)
{
	while (get_next_line(asmb->fd, &asmb->line) > 0)
	{
		if (str_has(asmb->line, LABEL) || str_has(asmb->line, COMMAND))
			get_lca(asmb);
		else if (!is_comment(asmb->line))
			ft_error("Error");
		if (asmb->line)
		{
			asmb->last_line_size = ft_strlen(asmb->line);
			ft_strdel(&asmb->line);
		}
	}
	(!check_last_line(asmb)) ? ft_error("Error") : 0;
}

void		parsing(t_asm *asmb)
{
	get_header(asmb);
	get_commands(asmb);
	if (!asmb->command)
		ft_error("Error");
	asmb->prog_size = compute_variables(asmb->command); // SEGFAULT CAN BE HERE.
}

void	check_argvs(t_asm *asmb, char **av, int ac)
{
	while (--ac > 0)
	{
		if (ft_strequ(av[ac], "-a"))
			asmb->flag_a = 1;
		else if (!asmb->file_name)
			asmb->file_name = ft_strdup(av[ac]);
	}
}

int		main(int ac, char **av)
{
	t_asm	*asmb;

	if (ac == 1)
		ft_putstr("Usage: ./asm [-a] <sourcefile.s>\n\
    -a : Instead of creating a .cor file, outputs a \
stripped and annotated version of the code to the standard output\n");
	else
	{
		asmb = init_asmb();
		check_argvs(asmb, av, ac);
		if (!asmb->file_name ||
			(asmb->fd = open(asmb->file_name, O_RDONLY)) < 0 ||
			read(asmb->fd, 0, 0) == -1)
			ft_error(ERR_FILE);
		parsing(asmb);

		prohodochka(asmb);

		// (asmb->flag_a) ? show_bot(asmb) : create_binary(asmb);
		// close(asmb->fd);
	}
	return (0);
}
