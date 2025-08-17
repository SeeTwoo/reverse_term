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

#include "screen.h"
#include "window.h"

void	cursor_blink_on(t_x11 *x11, t_grid *grid);

void	render_printable(t_x11 *x11, t_grid *grid, t_render_op *op) {
	int		x;
	int		y;
	char	*s;

	x = (op->x * x11->tile_width) + x11->margin;
	y = (op->y * x11->tile_height) + x11->tile_height;
	s = &grid->screen[op->y][op->x];
	XDrawImageString(x11->display, x11->win, x11->gc, x, y, s, 1);
	cursor_blink_on(x11, grid);
	XFlush(x11->display);
}

void	render_line_erasing(t_x11 *x11, t_grid *grid, t_render_op *op) {
	int		x;
	int		y;

	(void)grid;
	x = x11->margin;
	y = op->y * x11->tile_height;
	XClearArea(x11->display, x11->win,
		x, y + x11->font->descent,
		x11->tile_width * grid->width, x11->tile_height,
		false);
//	XDrawString(x11->display, x11->win, x11->gc, x, y + x11->tile_height, s, GRID_W);
	XFlush(x11->display);
}

#include <stdio.h>
void	full_redraw(t_x11 *x11, t_grid *grid, t_render_op *op) {
	unsigned int	y;

	(void)op;
	XClearWindow(x11->display, x11->win);
	y = 0;
	while (y < grid->height) {
		XDrawString(x11->display, x11->win, x11->gc,
			x11->margin, (y * x11->tile_height) + x11->tile_height,
			grid->screen[y], grid->width
		);
		y++;
	}
	XFlush(x11->display);
	grid->full_redraw = false;
}

void	render_character_deletion(t_x11 *x11, t_grid *grid, t_render_op *op) {
	XClearArea(x11->display, x11->win,
		(op->x * x11->tile_width) + x11->margin,
		(op->y * x11->tile_height) + x11->font->descent,
		x11->tile_width * (grid->width - op->x), x11->tile_height,
		false
	);
}

#include <stdio.h>
void	render(t_x11 *x11, t_grid *grid) {
	int	i;

	if (grid->full_redraw == true) {
		full_redraw(x11, grid, NULL);
		return ;
	}
	i = 0;
	while (grid->operations[i].type != END_LIST && i < 4096) {
		grid->render_operation_functions[grid->operations[i].type]
			(x11, grid, &grid->operations[i]);
		i++;
	}
}
