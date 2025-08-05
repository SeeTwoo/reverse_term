/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:22:25 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/05 07:34:24 by seetwoo          ###   ########.fr       */
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
	x11->font = XLoadQueryFont(x11->display, "fixed");
	if (!x11->font)
		return (FAILURE);
	return (SUCCESS);
}

int	init_window(t_x11 *x11) {
	x11->display = XOpenDisplay(NULL);
	if (!x11->display)
		return (FAILURE);
	x11->screen = DefaultScreen(x11->display);
	x11->root = RootWindow(x11->display, x11->screen);
	x11->win = XCreateSimpleWindow(x11->display, x11->root,
		100, 100,
		640, 400,
		1,
		WhitePixel(x11->display, x11->screen),
		BlackPixel(x11->display, x11->screen)
	);
	if (init_font(x11) == FAILURE)
		return (FAILURE);
	init_event(x11);
	return (SUCCESS);
}
