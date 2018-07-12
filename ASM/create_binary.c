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
	unsigned int	rew_magic;
	unsigned int	rew_bot_size;
	char 			prog_name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	char			null[4];
	unsigned int	bot_size = 15;

	ft_bzero(prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(comment, COMMENT_LENGTH + 1);
	ft_bzero(null, 4);
	ft_strcat(prog_name, "name");
	ft_strcat(comment, "comment");
	rew_magic = reverse_bytes(magic);
	rew_bot_size = reverse_bytes(bot_size);
	fd = open(name, O_RDWR | O_TRUNC | O_CREAT, 0777);

	write(fd, &rew_magic, 4);
	write(fd, &prog_name, PROG_NAME_LENGTH);
	write(fd, &null, 4);
	write(fd, &rew_bot_size, 4);
	write(fd, &comment, COMMENT_LENGTH);
	write(fd, &null, 4);

	close(fd);
	return (0);
}
