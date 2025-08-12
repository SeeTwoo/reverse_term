/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:22:25 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/12 14:33:49 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

int	init_event(t_x11 *x11) {
	XSelectInput(x11->display, x11->win,
		ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask);
	x11->wm_delete = XInternAtom(x11->display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(x11->display, x11->win, &x11->wm_delete, 1);
	return (SUCCESS);
}

int	init_font(t_x11 *x11) {
	x11->font = XLoadQueryFont(x11->display, "-misc-fixed-*-*-*-*-20-*-*-*-*-*-*-*");
	if (!x11->font)
		return (FAILURE);
	return (SUCCESS);
}

void	setup_minimal_size(t_x11 *x11, int window_width, int window_height) {
	XSizeHints	hints;

	hints.flags = PMinSize;
	hints.min_width = window_width;
	hints.min_height = window_height;
	XSetWMNormalHints(x11->display, x11->win, &hints);
}

int	init_window(t_x11 *x11) {
	int	window_width;
	int	window_height;

	x11->display = XOpenDisplay(NULL);
	if (!x11->display)
		return (FAILURE);
	if (init_font(x11) == FAILURE)
		return (FAILURE);
	x11->tile_height = x11->font->ascent + x11->font->descent;
	x11->tile_width = x11->font->max_bounds.width;
	x11->screen = DefaultScreen(x11->display);
	x11->root = RootWindow(x11->display, x11->screen);
	window_width = GRID_W * x11->tile_width + 2 * MARGIN;
	window_height = GRID_H * x11->tile_height + 2 * MARGIN;
	x11->win = XCreateSimpleWindow(x11->display, x11->root,
		100, 100,
		window_width, window_height,
		1,
		WhitePixel(x11->display, x11->screen),
		BlackPixel(x11->display, x11->screen)
	);
	init_event(x11);
	setup_minimal_size(x11, window_width, window_height);
	return (SUCCESS);
}
