#include "../libft/libft.h"
#include <stdio.h>

int		main()
{
	char	*line = "Hello, world!";

	printf("%d\n", line);
	printf("%d\n", ft_strstr(line, "lo,") - line + ft_strlen("lo,"));
	return (0);
}