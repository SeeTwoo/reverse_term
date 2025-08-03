/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_runtime.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 03:23:06 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/03 05:42:45 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

void	init_gc(t_term *term) {
	term->gc = XCreateGC(term->display, term->win, 0, NULL);
	XSetFont(term->display, term->gc, term->font->fid);
	XSetForeground(term->display, term->gc, WhitePixel(term->display, term->screen));
}

	//execlp("~/Documents/reverse_term/hello_world/hello_world.out", NULL,);
void	launch_hello_world(t_term *term) {
	(void)term;
	execlp("./hello_world/hello_world.out", "hello_world", NULL);
	exit(EXIT_FAILURE);
}

void	fill_output(t_term *term) {
	int	bytes_read;

	bytes_read = read(term->parent_fd, term->output, 255);
	term->output[bytes_read] = '\0';
}

void	term_runtime(t_term *term) {
	pid_t	pid;

	init_gc(term);
	XMapWindow(term->display, term->win);
	pid = forkpty(&term->parent_fd, NULL, NULL, NULL);
	if (pid == 0)
		launch_hello_world(term);
	while (1) {
		XNextEvent(term->display, &term->event);
		if (term->event.type == Expose) {
			fill_output(term);
			XDrawString(term->display, term->win, term->gc, 50, 50, term->output, strlen(term->output));
		}
		if (term->event.type == ClientMessage && (Atom)term->event.xclient.data.l[0] == term->wm_delete)
			break ;
		if (term->event.type == KeyPress || term->event.type == ButtonPress)
			break ;
	}
}
