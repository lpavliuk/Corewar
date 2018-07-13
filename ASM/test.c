#include "../libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

static char		*g_cmd_names[] = {
	"name1", "name2", "name3"
};

static int 		g_cmd_srray_size = 3;

int	main()
{
	int i;
	char	*flag = "name2";

	i = 0;
	while (i < g_cmd_srray_size)
	{
		if (ft_strncmp(g_cmd_names[i], flag, ft_strlen(g_cmd_names[i])) == 0)
			printf("1\n");
		else
			printf("0\n");
		i++;
	}
	return (0);
}
