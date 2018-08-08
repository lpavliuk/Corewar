/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 12:25:41 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/07 12:25:43 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/*
******************************************************************************
***************************** Virtual Machine ********************************
******************************************************************************
*/

# define ERR_101 "{red}Error: {yellow}\n"

/*
******************************************************************************
***************************** Visualisation **********************************
******************************************************************************
*/

# define ERR_201 "{red}Error: {yellow}memory was not allocated{eoc}\n"

/*
******************************************************************************
**************************** Network Game Mode *******************************
******************************************************************************
*/

# define ERR_301 "{red}Error: {yellow}failed connect to the server{eoc}\n"
# define ERR_302 "{red}Error: {yellow}there isn't player{eoc}\n"
# define ERR_303 "{red}Error: {yellow}failed accept client{eoc}\n"
# define ERR_304 "{red}Error: {yellow}there aren't players for game{eoc}\n"
# define ERR_305 "{red}Error: {yellow}server socket doesn't active{eoc}\n"
# define ERR_306 "{red}Error: {yellow}failed create socket{eoc}\n"
# define ERR_307 "{red}Error: {yellow}invalid IP{eoc}\n"
# define ERR_308 "{red}Error: {yellow}this IP address is busy{eoc}\n"

#endif
