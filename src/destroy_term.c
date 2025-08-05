/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_term.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:33:19 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/05 07:24:08 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

void	destroy_term(t_x11 *x11) {
	XUnloadFont(x11->display, x11->font->fid);
	XFreeGC(x11->display, x11->gc);
	XDestroyWindow(x11->display, x11->win);
	XCloseDisplay(x11->display);
}
