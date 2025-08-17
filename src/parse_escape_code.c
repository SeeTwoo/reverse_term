/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_escape_code.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 03:49:04 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/12 13:15:25 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "screen.h"

#ifndef BASE_10
# define BASE_10 "0123456789"
#endif

#ifndef MAX_VT100_ARG_NBR
# define MAX_VT100_ARG_NBR 16
#endif

int	get_args(char **buffer, int *args) {
	int	ac;

	ac = 0;
	while (1) {
		if (isalpha(**buffer) || !isdigit(**buffer) || !(**buffer))
			return (ac);
		args[ac] = (int)strtol(*buffer, buffer, 10);
		ac++;
		if (**buffer == ';')
			(*buffer)++;
	}
}

void	parse_escape_code(t_grid *grid, char **buffer) {
	int	args[MAX_VT100_ARG_NBR];
	int	ac;

	//print_raw_buffer(*buffer);
	(*buffer)++;
	skip_to_args(buffer);
	if (!(**buffer))
		return ;
	ac = get_args(buffer, args);
	if (ac == -1)
		return ;
	printf("command is %c\n", **buffer);
	grid->command_functions[(int)(**buffer - 'A')](grid, args, ac);
	(*buffer)++;
}
