/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_escape_code.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 03:49:04 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/07 08:12:24 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

#ifndef DIGITS
# define DIGITS "0123456789"
#endif

int	get_args(char *buffer, int *args, int *i) {
	int	j;

	j = 0;
	while (buffer[*i] && !isalpha(buffer[*i])) {
		args[j] = atoi(&buffer[*i]);
		while (isdigit(buffer[*i]))
			(*i)++;
		j++;
		if (buffer[*i] == ';')
			(*i)++;
		if (isalpha(buffer[*i]))
			break ;
		if (!isdigit(buffer[*i]))
			return (-1);
	}
	if (!isalpha(buffer[*i]))
		return (-1);
	return (j);
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

int	parse_escape_code(t_grid *grid, char *buffer) {
	int	i;
	int	args[10];
	int	ac;

	(void)grid;
	i = 1;
	if (buffer[i] == '[')
		i++;
	if (buffer[i] == '?')
		i++;
	else if (!buffer[i])
		return (i);
	ac = get_args(buffer, args, &i);
	if (ac == -1)
		return (i);
	if (buffer[i] == 'H')
		cursor_movement(grid, args, ac);
	else if (buffer[i] == 'J')
		erase_display(grid, args, ac);
	i++;
	return (i);
}
