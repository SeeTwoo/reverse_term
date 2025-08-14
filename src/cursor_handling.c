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

#include <X11/Xlib.h>
#include "window.h"
#include "screen.h"

void	swap_background_foreground_color(t_cell *cell) {
	int	temp;

	temp = cell->background_color;
	cell->background_color = cell->foreground_color;
	cell->foreground = term;
}

void	cursor_blink(t_x11 *x11, t_grid *grid) {
	int		x;
	int		y;
	char	*s;

	swap_background_foreground_color(&grid->screen[grid->y][grid->x]);
	x = (grid->x * x11->tile_width) + x11->margin;
	y = grid->y * x11->tile_height;
	s = &grid->screen[grid->y][grid->x]->c;
	XClearArea(x11->display, x11->win, x, y + x11->font->descent,
		x11->tile_width, x11->tile_height, false);
	change_gc_colors(&x11->gc, 
	XDrawString(x11->display, x11->win, x11->gc, x, y + x11->tile_height, s, 1);
	if (x11->cursor_on == true)
		x11->corsor_on == false;
	else
		x11->culsor_on == true;
}
