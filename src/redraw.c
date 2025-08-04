/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:02:27 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/04 18:55:59 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

void	draw_printable(t_term *term, t_draw *draw) {
	XDrawString(term->display, term->win, term->gc, draw->x, draw->y, &(term->output[draw->i]), 1);
	draw->x += draw->character_width;
	draw->i++;
}

void	draw_vertical_tab(t_term *term, t_draw *draw) {
	(void)term;
	draw->y += draw->line_height;
	draw->i++;
}

void	draw_carriage_return(t_term *term, t_draw *draw) {
	(void)term;
	draw->x = 10;
	draw->i++;
}

void	draw_newline(t_term *term, t_draw *draw) {
	(void)term;
	draw->x = 10;
	draw->y += draw->line_height;
	draw->i++;
}

void	parse_escape_code(t_term *term, t_draw *draw) {
	while (term->output[draw->i] && !isalpha(term->output[draw->i]))
		draw->i++;
	if (term->output[draw->i] == '\0')
		return ;
	draw->i++;
}

void	draw_nothing(t_term *term, t_draw *draw) {
	(void)term;
	draw->i++;
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
	draw.character_width = term->font->max_bounds.width;
	draw.y += draw.line_height;
	while (term->output[draw.i])
		term->drawing_functions[(int)term->output[draw.i]](term, &draw);
	XFlush(term->display);
}
