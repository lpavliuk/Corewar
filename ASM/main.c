#include "asm.h"

void	ft_error(char *str)
{
	ft_printf(str);
	exit(0);
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

int		main(int ac, char **av)
{
	int	fd;
	int i; //DELETE IT
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
		while (i < MAX_TABLE)
		{
			ft_printf("name: %s | label_size: %d | hex: %s |\n", NAME(i), LABEL_SIZE(i), HEX(i));
			i++;
		}
		// parsing(fd, s);
	}
	return (0);
}