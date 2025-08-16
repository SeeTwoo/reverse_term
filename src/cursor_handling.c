/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 00:13:04 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/07 03:15:46 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "window.h"
#include "screen.h"

void	cursor_blink_on(t_x11 *x11, t_grid *grid) {
	gc_bg_fg_swap(x11);
	XDrawImageString(x11->display, x11->win, x11->gc,
		(grid->x * x11->tile_width) + x11->margin,
		(grid->y * x11->tile_height) + x11->tile_height,
		&grid->screen[grid->y][grid->x],
		1
	);
	gc_bg_fg_swap(x11);
	x11->cursor_on = false;
	XFlush(x11->display);
}

void	cursor_blink_off(t_x11 *x11, t_grid *grid) {
	XDrawImageString(x11->display, x11->win, x11->gc,
		(grid->x * x11->tile_width) + x11->margin,
		(grid->y * x11->tile_height) + x11->tile_height,
		&grid->screen[grid->y][grid->x],
		1
	);
	x11->cursor_on = true;
	XFlush(x11->display);
}

void	cursor_blink(t_x11 *x11, t_grid *grid) {
	if (x11->cursor_on == true)
		cursor_blink_on(x11, grid);
	else
		cursor_blink_off(x11, grid);
}
