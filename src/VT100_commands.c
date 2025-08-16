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

//0 will erase from the cursor to the end of the screen
//1 will erase from the cursor to the beginning of the screen
//2 will erase the whole screen
void	J_erase_display(t_grid *grid, int *args, int ac) {
	(void)ac;
	if (args[0] == 0)
		memset(&grid->screen[grid->y][grid->x], ' ',
			(grid->width - grid->x) + ((grid->height - grid->y) * grid->width));
	else if (args[0] == 1)
		memset(grid->screen[0], ' ', 
			(grid->width - grid->x) + ((grid->height - grid->y) * grid->width));
	else if (args[0] == 2)
		memset(grid->screen[0], ' ',
			grid->width * grid->height);
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
		memset(&grid->screen[grid->y][grid->x], ' ', grid->width - grid->x);
	if (args[0] == 1)
		memset(grid->screen[grid->y], ' ', grid->x + 1);
	if (args[0] == 2)
		memset(grid->screen[grid->y], ' ', grid->width);
}
