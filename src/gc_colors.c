/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   gc_colors.c                                         :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                 +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

void	gc_bg_fg_swap(t_x11 *x11) {
	XGCValues	values;

	XGetGCValues(x11->display, x11->gc, GCForeground | GCBackground, &values);
	XSetForeground(x11->display, x11->gc, values.background);
	XSetBackground(x11->display, x11->gc, values.foreground);
}
