/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:22:25 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/03 03:40:11 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

int	init_font(t_term *term) {
	term->font = XLoadQueryFont(term->display, "fixed");
	if (!term->font)
		return (FAILURE);
	return (SUCCESS);
}

int	init_window(t_term *term) {
	term->display = XOpenDisplay(NULL);
	if (!term->display)
		return (FAILURE);
	term->screen = DefaultScreen(term->display);
	term->root = RootWindow(term->display, term->screen);
	term->win = XCreateSimpleWindow(term->display, term->root,
		100, 100,
		640, 400,
		1,
		WhitePixel(term->display, term->screen),
		BlackPixel(term->display, term->screen)
	);
	if (init_font(term) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
