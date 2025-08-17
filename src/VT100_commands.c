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

void	print_grid(t_grid *grid);

void	command_nothing(t_grid *grid, int *args, int ac) {
	(void)grid;
	(void)args;
	(void)ac;
}

void	H_cursor_movement(t_grid *grid, int *args, int ac) {
	if (ac != 2) {
		args[0] = 1;
		args[1] = 1;
	}
	grid->x = args[1] - 1;
	grid->y = args[0] - 1;
}

void	P_delete_character(t_grid *grid, int *args, int ac) {
	if (ac == 0)
		args[0] = 1;
	memmove(&grid->screen[grid->y][grid->x],
		&grid->screen[grid->y][grid->x + args[0]],
		(grid->width - (grid->x + 1) - args[0]) + (grid->width * (grid->height - grid->y + 1))
	);
	new_render_op(grid, DELETE_CHARACTER, grid->x, grid->y);
	//print_grid(grid);
}
