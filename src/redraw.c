/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:02:27 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/04 21:40:20 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

void	draw_printable(t_term *term, t_draw *draw) {
	int	x;
	int	y;

	x = (draw->x * draw->character_width) + MARGIN;
	y = (draw->y * draw->line_height) + draw->line_height;
	XDrawString(term->display, term->win, term->gc, x, y, &(term->output[draw->i]), 1);
	draw->x++;
	draw->i++;
}

void	draw_vertical_tab(t_term *term, t_draw *draw) {
	(void)term;
	draw->y++;
	draw->i++;
}

void	draw_carriage_return(t_term *term, t_draw *draw) {
	(void)term;
	draw->x = 0;
	draw->i++;
}

void	draw_newline(t_term *term, t_draw *draw) {
	(void)term;
	draw->x = 0;
	draw->y++;
	draw->i++;
}

void	draw_tab(t_term *term, t_draw *draw) {
	(void)term;
	draw->x += SPACES_PER_TAB - (draw->x % SPACES_PER_TAB);
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
	draw.x = 0;
	draw.y = 0;
	draw.line_height = term->font->ascent + term->font->descent;
	draw.character_width = term->font->max_bounds.width;
	while (term->output[draw.i])
		term->drawing_functions[(int)term->output[draw.i]](term, &draw);
	XFlush(term->display);
}
