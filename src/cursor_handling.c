/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 00:13:04 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/07 02:13:06 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

int wipe_cursor(t_x11 *x11, int cursor_x, int cursor_y) {
	int	x;
	int	y;

	x = (cursor_x * x11->tile_width) + MARGIN;
	y = cursor_y * x11->tile_height;
	XClearArea(x11->display, x11->win, x, y, x11->tile_width, x11->tile_height, false);
	XFlush(x11->display);
	return (0);
}

int	cursor_blink_on(t_x11 *x11, t_grid *grid) {
	int	x;
	int	y;

	x = (grid->x * x11->tile_width) + MARGIN;
	y = grid->y * x11->tile_height;
	XFillRectangle(x11->display, x11->win, x11->gc, x, y, x11->tile_width, x11->tile_height);
	x11->cursor_blink = false;
	XFlush(x11->display);
	return (0);
}

int	cursor_blink_off(t_x11 *x11, t_grid *grid) {
	wipe_cursor(x11, grid->x, grid->y);
	x11->cursor_blink = true;
	return (0);
}

int	cursor_handling(t_x11 *x11, t_grid *grid) {
	if (x11->cursor_blink == true)
		cursor_blink_on(x11, grid);
	else
		cursor_blink_off(x11, grid);
	return (0);
}
