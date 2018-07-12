#include "asm.h"

void	ft_error(char *str)
{
	ft_printf("%s\n", str);
	exit(0);
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

// void	get_commands(t_asm *asmb)
// {
	
// }

void		parsing(t_asm *asmb)
{
	get_header(asmb);
	// get_commands(asmb);
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

		// (asmb->flag_a) ? show_bot(asmb) : create_binary(asmb);
		// close(asmb->fd);
	}
	return (0);
}
