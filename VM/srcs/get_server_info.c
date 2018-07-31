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

static char				is_uchar(char *s)
{
	int					num;
	unsigned char		i;

	num = 0;
	i = 0;
	while (ft_isdigit(s[i]) && i < 3)
		num = num * 10 + s[i++] - '0';
	return ((i == 0 || s[i] != '\0' || num > 255) ? 0 : 1);
}

static char				is_ushort(char *s)
{
	int					num;
	unsigned char		i;

	num = 0;
	i = 0;
	while (ft_isdigit(s[i]) && i < 6)
		num = num * 10 + s[i++] - '0';
	return ((i == 0 || s[i] != '\0' || num > 65535) ? 0 : 1);
}

static char				*get_ip(char *s)
{
	char				**octets;
	unsigned char		i;
	unsigned char		n_commas;

	(!(octets = ft_strsplit(s, '.'))) ? ft_error("Error") : 0;
	i = 0;
	while (octets[i])
		(!is_uchar(octets[i])) ? ft_error("Error") : ft_strdel(&octets[i++]);
	(i != 4) ? ft_error("Error") : free(octets);
	i = 0;
	n_commas = 0;
	while (s[i])
	{
		(s[i] == '.') ? (n_commas++) : 0;
		(n_commas > 3) ? ft_error("Error") : 0;
		i++;
	}
	return (s);
}

static unsigned short	get_port(char *s)
{
	if (!is_ushort(s) || ft_atoi(s) == 0)
		ft_error("Error");
	return ((unsigned short)ft_atoi(s));
}

void					get_server_info(t_vm *vm, char *args[], int argv, int *i)
{
	vm->flag_server = 1;
	(*i)++;
	if (*i >= argv)
		ft_error("Error");
	else
		vm->ip = get_ip(args[*i]);
	(*i)++;
	if (*i >= argv)
		ft_error("Error");
	else
		vm->port = get_port(args[*i]);
}

// void					get_info_server(t_vm *vm, char *args[], int argv, int *i)
// {
// 	vm->flag_server = 1;
// 	(*i)++;
// 	if (*i >= argv)
// 		ft_error("Error");
// 	else
// 		vm->ip = args[*i];
// }

// void					get_info_client(t_vm *vm, char *args[], int argv, int *i)
// {
// 	vm->flag_client = 1;
// 	(*i)++;
// 	if (*i >= argv)
// 		ft_error("Error");
// 	else
// 		vm->ip = args[*i];
// }
