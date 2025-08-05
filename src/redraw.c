/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:02:27 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/05 20:15:07 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

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

void	redraw(t_x11 *x11, t_grid *grid) {
	int	x;
	int y;

	printf("hello\n");
	if (grid->full_redraw == true) {
		full_redraw(x11, grid);
		return ;
	}
	x = (grid->x_draw * x11->tile_width) + MARGIN;
	y = (grid->y_draw * x11->tile_height) + x11->tile_height;
	XDrawString(x11->display, x11->win, x11->gc,
		x, y, &grid->grid[grid->y_draw][grid->x_draw], GRID_W - grid->x_draw);
	grid->x_draw = grid->x;
	grid->y_draw = grid->y;
	XFlush(x11->display);
}
