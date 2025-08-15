/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VT100_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 13:15:37 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/12 14:21:25 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "screen.h"

void	H_cursor_movement(t_grid *grid, int *args, int ac) {
	if (ac != 2) {
		args[0] = 1;
		args[1] = 1;
	}
	grid->x = args[1] - 1;
	grid->y = args[0] - 1;
}

void	erase_line(t_grid *grid, int start, int finish, int y) {
	int	x;

	x = start;
	while (x < finish) {
		grid->screen[y][x].c = ' ';
		x++;
	}
}

void	erase_several_lines(t_grid *grid, int start, int finish) {
	int	y;

	y = start;
	while (y < finish) {
		erase_line(grid, 0, grid->width - 1, y);
		y++;
	}
}

//0 will erase from the cursor to the end of the screen
//1 will erase from the cursor to the beginning of the screen
//2 will erase the whole screen
void	J_erase_display(t_grid *grid, int *args, int ac) {
	(void)ac;
	if (args[0] == 0) {
		erase_line(grid, grid->x, grid->width - 1, grid->y);
		erase_several_lines(grid, grid->y + 1, grid->height - 1);
	} else if (args[0] == 1) {
		erase_line(grid, 0, grid->x, grid->y);
		erase_several_lines(grid, 0, grid->y - 1);
	} else if (args[0] == 2) {
		erase_several_lines(grid, 0, grid->height - 1);
	}
	new_render_op(grid, ERASE_DISPLAY, grid->x, grid->y);
	grid->full_redraw = true;
}

//0 will erase from the cursor to the end of the line
//1 will erase from the cursor to the beginning of the line
//2 will erase the whole screen
void	K_erase_line(t_grid *grid, int *args, int ac) {
	if (ac == 0)
		args[0] = 0;
	if (args[0] == 0)
		erase_line(grid, grid->x, grid->width - 1, grid->y);
	if (args[0] == 1)
		erase_line(grid, 0, grid->x, grid->y);
	if (args[0] == 2)
		erase_line(grid, 0, grid->width - 1, grid->y);
}
