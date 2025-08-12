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

#include "reverse_term.h"

void	cursor_movement(t_grid *grid, int *args, int ac) {
	if (ac != 2) {
		args[0] = 1;
		args[1] = 1;
	}
	grid->x = args[1] - 1;
	grid->y = args[0] - 1;
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

//0 will erase from the cursor to the end of the line
//1 will erase from the cursor to the beginning of the line
//2 will erase the whole screen
void	erase_line(t_grid *grid, int *args, int ac) {
	if (ac == 0)
		args[0] = 0;
	if (args[0] == 0)
		memset(&grid->grid[grid->y][grid->x], ' ', GRID_W - grid->x);
	if (args[0] == 1)
		memset(&grid->grid[grid->y], ' ', grid->x);
	if (args[0] == 2)
		memset(&grid->grid[grid->y], ' ', GRID_W);
	new_render_op(grid, ERASE_LINE, grid->x, grid->y);
}
