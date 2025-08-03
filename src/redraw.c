/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:02:27 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/03 23:02:39 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

#ifndef WEIRD_CHARS
# define WEIRD_CHARS "\r\v"
#endif

void	new_line(t_draw *draw) {
	draw->i++;
	draw->y += draw->line_height;
}

void	vertical_tab(t_draw *draw, char c) {
	if (c == '\v')
		printf("vertical tab\n");
	else if (c == '\r')
		printf("carriage return\n");
	draw->i++;
}

void	parse_escape_code(t_term *term, t_draw *draw) {
	while (term->output[draw->i] && !isalpha(term->output[draw->i]))
		draw->i++;
	if (term->output[draw->i] == '\0')
		return ;
	draw->i++;
}

void	draw_bit(t_term *term, t_draw *draw) {
	draw->line_len = strcspn(&(term->output[draw->i]), "\x1b\n");
	XDrawString(term->display, term->win, term->gc, draw->x, draw->y, &(term->output[draw->i]), draw->line_len);
	draw->i += draw->line_len;
}

void	redraw(t_term *term) {
	t_draw	draw;
	
	printf("\e[31m hello, redrawing\e[0m\n");
	fflush(stdout);
	print_current_buffer(term);
	XClearWindow(term->display, term->win);
	draw.i = 0;
	draw.x = 10;
	draw.y = 0;
	draw.line_height = term->font->ascent + term->font->descent + 5;
	draw.y += draw.line_height;
	while (term->output[draw.i]) {
		if (term->output[draw.i] == '\x1b') {
			parse_escape_code(term, &draw);
		} else if (term->output[draw.i] == '\n') {
			new_line(&draw);
		} else if (term->output[draw.i] == '\r') {
			vertical_tab(&draw, term->output[draw.i]);
		} else if (term->output[draw.i] == '\v') {
			vertical_tab(&draw, term->output[draw.i]);
		} else {
			draw_bit(term, &draw);
		}
	}
	XFlush(term->display);
}
