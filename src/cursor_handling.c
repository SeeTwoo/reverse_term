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

void	cursor_blink(t_x11 *x11, t_grid *grid) {
	int		x;
	int		y;
	char	*s;

	if (x11->cursor_on == true)
		gc_bg_fg_swap(x11);
	x = (grid->x * x11->tile_width) + x11->margin;
	y = grid->y * x11->tile_height;
	s = &grid->screen[grid->y][grid->x];
	XClearArea(x11->display, x11->win, x, y + x11->font->descent,
		x11->tile_width, x11->tile_height, false);
	XDrawImageString(x11->display, x11->win, x11->gc,
		x, y + x11->tile_height, s, 1);
	if (x11->cursor_on == true) {
		gc_bg_fg_swap(x11);
		x11->cursor_on = false;
	} else {
		x11->cursor_on = true;
	}
	XFlush(x11->display);
}
