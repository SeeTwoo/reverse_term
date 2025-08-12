/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_escape_code.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 03:49:04 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/12 02:35:00 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

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

void	cursor_movement(t_grid *grid, int *args, int ac) {
	if (ac != 2) {
		args[0] = 0;
		args[1] = 0;
	}
	grid->x = args[1];
	grid->y = args[0];
}

//0 will erase from the cursor to the end of the screen
//1 will erase from the cursor to the beginning of the screen
//2 will erase the whole screen
//someone will have to do some thinking on the preciseness of the 0 and 1 parameter
//like calculating the length properly
void	erase_display(t_grid *grid, int *args, int ac) {
	(void)ac;
	if (args[0] == 0)
		memset(&grid->grid[grid->y][grid->x], ' ', (GRID_W - grid->x) + ((GRID_H - grid->y) * GRID_W));
	if (args[0] == 1)
		memset(grid->grid, ' ', grid->y * GRID_W);
	if (args[0] == 2)
		memset(grid->grid, ' ', GRID_W * GRID_H);
	new_render_op(grid, ERASE_DISPLAY, grid->x, grid->y);
	grid->full_redraw = true;
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
	if (**buffer == 'H')
		cursor_movement(grid, args, ac);
	else if (**buffer == 'J')
		erase_display(grid, args, ac);
	(*buffer)++;
}
