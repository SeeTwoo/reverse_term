/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:02:27 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/05 09:33:00 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

void	redraw(t_term *term, t_x11 *x11, t_grid *grid) {
	int	y;
	int	line_height;

	(void)term;
	XClearWindow(x11->display, x11->win);
	y = 0;
	line_height = x11->font->ascent + x11->font->descent;
	while (y < 25) {
		XDrawString(x11->display, x11->win, x11->gc,
			MARGIN, (y *line_height) + line_height,
			grid->grid[y], 80
		);
		y++;
	}
	XFlush(x11->display);
}
