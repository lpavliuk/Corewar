#include "asm.h"

void	ft_error(char *str)
{
	ft_printf("%s\n", str);
	exit(0);
}

// void		ft_syntax(int i, int j)
// {
// 	ft_printf("Syntax error at [%.3d:%.3d]\n", i, j);
// 	exit(0);
// }

t_asm			*init_asmb(void)
{
	t_asm		*s;

	if (!(s = (t_asm*)malloc(sizeof(t_asm))))
		ft_error("Error [init_asmb()]: memory was not allocated");
	ft_bzero(s->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(s->comment, COMMENT_LENGTH + 1);
	s->file_name = NULL;
	s->flag_a = 0;
	s->prog_size = 0;
	s->new_fd = 0;
	s->command = NULL;
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
	if (ft_strncmp(s, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) == 0)
		return (1);
	return (0);
}

char		is_bot_comment(char *s)
{
	if (!s)
		return (0);
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	if (ft_strncmp(s, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)) == 0)
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
** 2 functions for getting bot name.
** first function writes to name string in main structure called asmb.
** second check if it's valid name string and send this string int pieces.
*/

char	copy_to_dst(char *dst, char *src, int *j)
{
	static int i = 0;

	while (i < PROG_NAME_LENGTH && src[*j] && src[*j] != '\"')
	{
		dst[i] = src[*j];
		i++;
		*j++;
	}
	if (i == PROG_NAME_LENGTH && src[*j] != '\"')
	{
		ft_printf("Champion name too long (Max length %d)\n", PROG_NAME_LENGTH);
		exit(0);
	}
	else if (src[*j] == '\"')
		return (1);
	return (0);
}

void	add_name(char *dst, char **src, int fd, int *flag)
{
	int		j;

	(*flag & 1) ? ft_error("Error") : (*flag = *flag | 1);
	j = ft_strstr(*src, NAME_CMD_STRING) - *src + ft_strlen(NAME_CMD_STRING);
	while ((*src)[j] && ((*src)[j] == ' ' || (*src)[j] == '\t'))
		j++;
	((*src)[j] != '\"') ? ft_error("Error") : j++;
	while (*src && !copy_to_dst(dst, *src, &j))
	{
		j = 0;
		ft_strdel(src);
		get_next_line(fd, src);
	}
	(!*src) ? ft_error(ERROR_BRACKET) : 0;
	((*src)[j] != '\"') ? ft_syntax(*i, j + 1) : j++; // OR ERROR_BRACKET
	while ((*src)[j] && ((*src)[j] == ' ' || (*src)[j] == '\t'))
		j++;
	if ((*src)[j] != '#' && (*src)[j] != ';' && (*src)[j] != '\0')
		ft_error("Error");
	ft_strdel(src);
}

void	add_comment(char *dst, char **src, int fd, int *i)
{
	(*flag & 2) ? ft_error("Error") : (*flag = *flag | 2);
}

void	get_name_and_comment(int fd, t_asm *asmb)
{
	char	*line;
	char	flag; // 1 bit is for name, and 2 bit - for comment.

	line = 0;
	flag = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (is_bot_name(line))
			add_name(asmb->name, &line, fd, &flag);
		else if (is_bot_comment(line))
			add_comment(asmb->comment, &line, fd, &flag);
		else if (!is_comment(line))
			ft_error("Error");
		ft_strdel(&line);
	}
	(flag != 3) ? ft_error("Error\n") : 0;
}

// void	get_commands(int fd, t_asm *asmb)
// {

// }

void		parsing(int fd, t_asm *asmb)
{
	get_name_and_comment(fd, asmb, &i);
	// get_commands(fd, asmb, i);
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
	int	fd;
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
			(fd = open(asmb->file_name, O_RDONLY)) < 0 ||
			read(fd, 0, 0) == -1)
			ft_error(ERR_FILE);
		parsing(fd, asmb);
		// (asmb->flag_a) ? show_bot(asmb) : create_binary(asmb);
		// close(fd);
	}
	return (0);
}
