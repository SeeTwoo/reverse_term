/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_runtime.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 03:23:06 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/07 02:49:51 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

void	init_gc(t_x11 *x11) {
	x11->gc = XCreateGC(x11->display, x11->win, 0, NULL);
	XSetFont(x11->display, x11->gc, x11->font->fid);
	XSetForeground(x11->display, x11->gc, WhitePixel(x11->display, x11->screen));
}

void	term_runtime(t_x11 *x11, t_pty *pty, t_grid *grid) {
	struct timeval	tv;
	int				x_fd;
	int				max_fd;
	int				select_ret;
	fd_set			read_fds;

	init_gc(x11);
	XMapWindow(x11->display, x11->win);
	x_fd = ConnectionNumber(x11->display);
	max_fd = (x_fd > pty->parent_fd ? x_fd : pty->parent_fd) + 1;
	x11->cursor_blink = true;
	while (1) {
		tv.tv_sec = 0;
		tv.tv_usec = 500000;
		FD_ZERO(&read_fds);
		FD_SET(x_fd, &read_fds);
		FD_SET(pty->parent_fd, &read_fds);

		select_ret = select(max_fd, &read_fds, NULL, NULL, &tv);
		if (select_ret == -1) {
			perror("select");
			exit(EXIT_FAILURE);
		} else if (select_ret == 0) {
			cursor_handling(x11, grid);
			continue ;
		}

		if (FD_ISSET(pty->parent_fd, &read_fds)) {
			wipe_cursor(x11, grid->x, grid->y);
			if (fill_grid(pty, grid) == FAILURE)
				exit(EXIT_FAILURE);
			render(x11, grid);
		}

		if (FD_ISSET(x_fd, &read_fds)) {
			do {
				XNextEvent(x11->display, &x11->event);
				if (x11->event.type == ClientMessage && (Atom)x11->event.xclient.data.l[0] == x11->wm_delete)
					exit_term(pty ,x11);
				if (x11->event.type == KeyPress)
					handle_keypress(x11, pty);
				if (x11->event.type == Expose)
					render(x11, grid);
			} while (XPending(x11->display));
		}
	}
}
