#include "asm.h"

void	ft_error(char *str)
{
	ft_printf(str);
	exit(0);
}

char		key_check(int ac, char **av, char *needle)
{
	int		i;

	i = 0;
	while (i < ac)
	{
		if (ft_strequ(av[i], needle))
			return (1);
		i++;
	}
	return (0);
}

t_asm			*init_asmb(void)
{
	t_asm		*s;

	if (!(s = (t_asm*)malloc(sizeof(t_asm))))
		ft_error("Error\n");
	ft_bzero(s->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(s->comment, COMMENT_LENGTH + 1);
	s->prog_size = 0;
	s->new_fd = 0;
	s->command = NULL;
	return (s);
}

void	get_bot_name(t_asm *asmb, char *line, char *flag)
{
	(*flag & 1) ? ft_error("Error\n") : (*flag = *flag | 1);
	
}

void	get_bot_comment(t_asm *asmb, char *line, char *flag)
{

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
			add_name(asmb, line, &flag);
		else if (is_bot_comment(line))
			add_bot_comment(asmb, line, &flag);
		else if (!is_comment(line))
			ft_error("Error\n");
		ft_strdel(&line);
	}
}

void	get_commands(int fd, t_asm *asmb)
{

}

void		parsing(int fd, t_asm *asmb)
{
	get_name_and_comment(fd, asmb);
	get_commands(fd, asmb);
}

int		main(int ac, char **av)
{
	int	fd;
	t_asm	*asmb;

	i = 0;
	if (ac == 1)
		ft_putstr("Usage: ./asm [-a] <sourcefile.s>\n\
    -a : Instead of creating a .cor file, outputs a \
stripped and annotated version of the code to the standard output\n");
	else
	{
		if ((fd = open(av[ac - 1], O_RDONLY)) < 0 || read(fd, 0, 0) == -1)
			ft_error("Error\n");
		asmb = init_asmb();
		parsing(fd, s);
		(key_check(ac, av, "-a")) ? show_bot(s) : create_binary(s);
		close(fd);
	}
	return (0);
}
