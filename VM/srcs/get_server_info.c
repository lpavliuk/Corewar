/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 14:03:16 by tkiselev          #+#    #+#             */
/*   Updated: 2018/07/19 14:03:20 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	get_info_server(char *args[], int argv, int *i)
{
	g_vm->flag_server = 1;
	(*i)++;
	if (*i >= argv)
		ft_error("Error");
	else
		g_vm->ip = args[*i];
}

void	get_info_client(char *args[], int argv, int *i)
{
	g_vm->flag_client = 1;
	(*i)++;
	if (*i >= argv)
		ft_error("Error");
	else
		g_vm->ip = args[*i];
}
