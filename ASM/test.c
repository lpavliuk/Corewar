#include "../libft/libft.h"
#include <stdio.h>


inline void	func()
{
	write(1, "Hello\n", 6);
}

int		main()
{
	char	*line = "Hello, world!";

	func();
	return (0);
}