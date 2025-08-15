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

#include "window.h"

void	init_gc(t_x11 *x11) {
	x11->gc = XCreateGC(x11->display, x11->win, 0, NULL);
	XSetFont(x11->display, x11->gc, x11->font->fid);
	XSetForeground(x11->display, x11->gc, WhitePixel(x11->display, x11->screen));
}

int	init_event(t_x11 *x11) {
	XSelectInput(x11->display, x11->win,
		ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask);
	x11->wm_delete = XInternAtom(x11->display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(x11->display, x11->win, &x11->wm_delete, 1);
	return (0);
}

int	init_font(t_x11 *x11) {
	x11->font = XLoadQueryFont(x11->display, "-misc-fixed-*-*-*-*-20-*-*-*-*-*-*-*");
	if (!x11->font)
		return (1);
	return (0);
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
		return (1);
	if (init_font(x11) == 1)
		return (1);
	x11->tile_height = x11->font->ascent + x11->font->descent;
	x11->tile_width = x11->font->max_bounds.width;
	x11->margin = 5;
	x11->screen = DefaultScreen(x11->display);
	x11->root = RootWindow(x11->display, x11->screen);
	window_width = 80 * x11->tile_width + 2 * x11->margin;
	window_height = 25 * x11->tile_height + 2 * x11->margin;
	x11->win = XCreateSimpleWindow(x11->display, x11->root,
		100, 100,
		window_width, window_height,
		1,
		WhitePixel(x11->display, x11->screen),
		BlackPixel(x11->display, x11->screen)
	);
	init_event(x11);
	init_gc(x11);
	setup_minimal_size(x11, window_width, window_height);
	return (0);
}
