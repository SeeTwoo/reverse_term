/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:22:25 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/03 02:30:50 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

int	init_window(t_term *term)
{
	term->display = XOpenDisplay(NULL);
	if (!term->display)
		return (1);
	term->screen = DefaultScreen(term->display);
	term->root = RootWindow(term->display, term->screen);
	term->win = XCreateSimpleWindow(term->display, term->root,
		100, 100,
		640, 400,
		1,
		WhitePixel(term->display, term->screen),
		BlackPixel(term->display, term->screen)
	);
	return (0);
}
