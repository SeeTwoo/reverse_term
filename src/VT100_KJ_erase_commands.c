/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   VT100_KJ_erase_commands.c                           :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                 +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "screen.h"

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
