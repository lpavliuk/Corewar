/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 13:17:12 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/01 13:17:13 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int i;

    i = 0;
    if (argv[1])
	    i = atoi(argv[1]);
	while (i >= 0)
	{
		printf("Time to start the game: %d\n", i);
		printf("Number of connected players: %d\n", 2);
		sleep(1);
		i--;
	}
}
