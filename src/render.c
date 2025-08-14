/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:02:27 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/12 14:20:24 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

void	render_printable(t_x11 *x11, t_grid *grid, t_render_op *op) {
	int		x;
	int		y;
	char	*s;

	x = (op->x * x11->tile_width) + MARGIN;
	y = (op->y * x11->tile_height) + x11->tile_height;
	s = &grid->grid[op->y][op->x];
	XDrawString(x11->display, x11->win, x11->gc, x, y, s, 1);
	XFlush(x11->display);
}

void	render_line_erasing(t_x11 *x11, t_grid *grid, t_render_op *op) {
	int		x;
	int		y;
	char	*s;

	x = MARGIN;
	y = op->y * x11->tile_height;
	s = &grid->grid[op->y][0];
	XClearArea(x11->display, x11->win,
		x, y + x11->font->descent,
		x11->tile_width * GRID_W, x11->tile_height,
		false);
	XDrawString(x11->display, x11->win, x11->gc, x, y + x11->tile_height, s, GRID_W);
	XFlush(x11->display);
}

void	full_redraw(t_x11 *x11, t_grid *grid) {
	int	y;

	XClearWindow(x11->display, x11->win);
	y = 0;
	while (y < GRID_H) {
		XDrawString(x11->display, x11->win, x11->gc,
			MARGIN, (y * x11->tile_height) + x11->tile_height,
			grid->grid[y], GRID_W
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
	while (grid->operations[i].type != END_LIST && i < 4096) {
		if (grid->operations[i].type == PRINTABLE)
			render_printable(x11, grid, &grid->operations[i]);
		else if (grid->operations[i].type == ERASE_DISPLAY)
			full_redraw(x11, grid);
		else if (grid->operations[i].type == ERASE_LINE)
			render_line_erasing(x11, grid, &grid->operations[i]);
		i++;
	}
	XFlush(x11->display);
}
