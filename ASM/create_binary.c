/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_binary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 13:32:46 by opavliuk          #+#    #+#             */
/*   Updated: 2018/07/12 13:32:47 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

unsigned int reverse_bytes(unsigned int x)
{
	unsigned int reversed;
	unsigned char *n1;
	unsigned char *n2;

	n1 = (unsigned char *)&x;
	n2 = (unsigned char *)&reversed;

	n2[0] = n1[3];
	n2[1] = n1[2];
	n2[2] = n1[1]; 
	n2[3] = n1[0];

	return (reversed);
}

int		main(void)
{
	int fd;
	unsigned char	binary[128] = "0xea83fe";
	char *name = "name.cor";
	unsigned int	magic = COREWAR_EXEC_MAGIC;
	unsigned int	rew_magic;

	rew_magic = reverse_bytes(magic);
	printf("%u\n", magic);
	printf("%u\n", rew_magic);
	fd = open(name, O_RDWR | O_TRUNC | O_CREAT, 0777);

	write(fd, &rew_magic, 4);
	write(fd, &magic, 4);

	close(fd);
	return (0);
}
