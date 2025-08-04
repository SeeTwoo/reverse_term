/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_runtime.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 03:23:06 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/04 20:15:51 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

void	init_gc(t_term *term) {
	term->gc = XCreateGC(term->display, term->win, 0, NULL);
	XSetFont(term->display, term->gc, term->font->fid);
	XSetForeground(term->display, term->gc, WhitePixel(term->display, term->screen));
}

	//execlp("~/Documents/reverse_term/hello_world/hello_world.out", NULL,);
void	launch_shell(t_term *term) {
	(void)term;
	execlp("/bin/bash", "bash", "--posix", NULL);
	exit(EXIT_FAILURE);
}

int	fill_output(t_term *term) {
	int	bytes_read;
	
	if (term->out_len >= sizeof(term->output) - 1)
		return (0);
	bytes_read = read(term->parent_fd, &(term->output[term->out_len]), sizeof(term->output) - term->out_len - 1);
	if (bytes_read <= 0)
		return (bytes_read);
	term->output[bytes_read + term->out_len] = '\0';
	term->out_len += bytes_read;
	return (bytes_read);
}

void	term_runtime(t_term *term) {
	int		x_fd;
	int		max_fd;
	fd_set	read_fds;

	init_gc(term);
	term->out_len = 0;
	term->output[0] = '\0';
	XMapWindow(term->display, term->win);
	term->shell_pid = forkpty(&term->parent_fd, NULL, NULL, NULL);
	if (term->shell_pid == 0)
		launch_shell(term);
	x_fd = ConnectionNumber(term->display);
	max_fd = (x_fd > term->parent_fd ? x_fd : term->parent_fd) + 1;
	while (1) {
		FD_ZERO(&read_fds);
		FD_SET(x_fd, &read_fds);
		FD_SET(term->parent_fd, &read_fds);

		if (select(max_fd, &read_fds, NULL, NULL, NULL) == -1) {
			perror("select");
			exit(EXIT_FAILURE);
		}

		if (FD_ISSET(term->parent_fd, &read_fds)) {
			if (fill_output(term) > 0)
				redraw(term);
			else
				exit(EXIT_SUCCESS);
		}

		if (FD_ISSET(x_fd, &read_fds)) {
			do {
				XNextEvent(term->display, &term->event);
				if (term->event.type == ClientMessage && (Atom)term->event.xclient.data.l[0] == term->wm_delete)
					exit_term(term);
				if (term->event.type == KeyPress)
					handle_keypress(term);
				if (term->event.type == Expose)
					redraw(term);
			} while (XPending(term->display));
		}
	}
}
