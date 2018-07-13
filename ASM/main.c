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
		command = command->next;
	}
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
	s->magic = 0;
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

char	check_last_line(char fd)
{
	char buf[1];

	lseek(fd, -1, SEEK_CUR);
	read(fd, &buf, 1);
	if (buf[0] == '\n')
		return (1);
	return (0);
}

int		index_of(char *needle)
{
	int i;

	i = 0;
	while (i < MAX_TABLE)
	{
		if (ft_strncmp(NAME(i), needle, ft_strlen(NAME(i))) == 0)
			return (1);
		i++;
	}
	return (-1);
}

char	str_has(char *str, char flag)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	skip_shit(str, &i, " \t");
	if (flag == LABEL)
	{
		while (str[i] && str[i] != ':')
			if (ft_strchr(LABEL_CHARS, str[i++]) == NULL)
				return (0);
		return ((str[i] == ':') ? 1 : 0);
	}
	else if (flag == COMMAND)
	{
		if (str_has(str, LABEL))
			i = ft_strchr(str, ':') - str + 1;
		skip_shit(str, &i, " \t");
		if (index_of(str + i) != -1)
			return (1);
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
	new->bytes_before = 0;
	new->bytes = 0;
	new->codage = 0;
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
	*j += 2; // skip ':'
}

void	get_labels(t_asm *asmb, t_command *new, int *j)
{
	char	*s;

	while (asmb->line)
	{
		s = asmb->line;
		skip_shit(s, j, " \t");
		if (str_has(s, LABEL))
			get_label(&new->labels, s, j);
		skip_shit(s, j, " \t");
		if (s[*j] != '\0' && !is_comment(s + *j))
			return ;
		*j = 0;
		ft_strdel(&s);
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
	new->opcode = index_of(new->name) + 1;
	(new->opcode == -1) ? ft_error("Error") : 0;
}

/*
** functions which gets arguments after cmd.
*/

void	get_arguments(t_asm *asmb, t_command *new, int j)
{
	char	**arr;

	if (!(arr = ft_strsplit(asmb->line + j, SEPARATOR_CHAR)))
		ft_error("Error");

}

void	get_lca(t_asm *asmb) // lca means label + command + arguments
{
	t_command		*new;
	int			j;

	j = 0;
	new = push_new_command(&asmb->command);
	get_labels(asmb, new, &j);
	if (str_has(asmb->line, COMMAND))
	{
		get_command(asmb, new, &j);
		get_arguments(asmb, new, j);
	}
}

void	get_commands(t_asm *asmb)
{
	while (get_next_line(asmb->fd, &asmb->line) > 0)
	{
		if (str_has(asmb->line, LABEL) || str_has(asmb->line, COMMAND))
			get_lca(asmb);
		else if (!is_comment(asmb->line))
			ft_error("Error");
		ft_strdel(&asmb->line);
	}
	(!check_last_line(asmb->fd)) ? ft_error("Error") : 0; // instead of 0 we need to execute function that will compute other variables.
}

void		parsing(t_asm *asmb)
{
	get_header(asmb);
	get_commands(asmb);
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
