/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_term.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:33:19 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/07 10:28:04 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/Xlib.h>
#include "window.h"

void	destroy_term(t_x11 *x11) {
	XFreeFont(x11->display, x11->font);
	XFreeGC(x11->display, x11->gc);
	XDestroyWindow(x11->display, x11->win);
	XCloseDisplay(x11->display);
}
