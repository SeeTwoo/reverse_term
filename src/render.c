/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:02:27 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/07 01:59:21 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

void	render_printable(t_x11 *x11, t_grid *grid, t_render_op *op) {
	int		x;
	int		y;
	char	*c;

	x = (op->x * x11->tile_width) + MARGIN;
	y = (op->y * x11->tile_height) + x11->tile_height;
	c = &grid->grid[op->y][op->x];
	XDrawString(x11->display, x11->win, x11->gc, x, y, c, 1);
}

void	render_backspace(t_x11 *x11, t_render_op *op) {
	int	x;
	int	y;

	x = (op->x * x11->tile_width) + MARGIN;
	y = op->y * x11->tile_height;
	XClearArea(x11->display, x11->win, x, y, x11->tile_width * 2, x11->tile_height, false);
}

void	full_redraw(t_x11 *x11, t_grid *grid) {
	int	y;

	XClearWindow(x11->display, x11->win);
	y = 0;
	while (y < GRID_H) {
		XDrawString(x11->display, x11->win, x11->gc,
			MARGIN, (y * x11->tile_height) + x11->tile_height,
			grid->grid[y], strnlen(grid->grid[y], GRID_W)
		);
		y++;
	}
	XFlush(x11->display);
	grid->full_redraw = false;
}

void	render(t_x11 *x11, t_grid *grid) {
	int	i;

	if (grid->full_redraw == true) {
		full_redraw(x11, grid);
		return ;
	}
	i = 0;
	while (grid->operations[i].type != END_LIST) {
		if (grid->operations[i].type == PRINTABLE)
			render_printable(x11, grid, &grid->operations[i]);
		else if (grid->operations[i].type == BACKSPACE)
			render_backspace(x11, &grid->operations[i]);
		i++;
	}
	XFlush(x11->display);
}
