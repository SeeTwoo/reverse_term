/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_runtime.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 03:23:06 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/03 16:07:10 by seetwoo          ###   ########.fr       */
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

	bytes_read = read(term->parent_fd, term->output, 255);
	term->output[bytes_read] = '\0';
	return (bytes_read);
}

void	term_runtime(t_term *term) {
	pid_t	pid;
	int		X_fd = ConnectionNumber(term->display);
	int		max_fd = (X_fd > term->parent_fd ? X_fd : term->parent_fd) + 1;

	init_gc(term);
	XMapWindow(term->display, term->win);
	XFlush(term->display);
	pid = forkpty(&term->parent_fd, NULL, NULL, NULL);
	if (pid == 0)
		launch_shell(term);
	while (1) {
		fd_set	read_fds;
		FD_ZERO(&read_fds);
		FD_SET(X_fd, &read_fds);
		FD_SET(term->parent_fd, &read_fds);

		if (select(max_fd, &read_fds, NULL, NULL, NULL) == -1) {
			perror("select");
			exit(EXIT_FAILURE);
		}

		if (FD_ISSET(X_fd, &read_fds)) {
			while (XPending(term->display)) {
				XNextEvent(term->display, &term->event);
				if (term->event.type == ClientMessage && (Atom)term->event.xclient.data.l[0] == term->wm_delete)
					exit(EXIT_SUCCESS);
				if (term->event.type == KeyPress)
					handle_keypress(term);
			}
		}

		if (FD_ISSET(term->parent_fd, &read_fds)) {
			if (fill_output(term) > 0) {
				printf("buffer is %s\n", term->output);
				XClearWindow(term->display, term->win);
				XDrawString(term->display, term->win, term->gc, 50, 50, term->output, strlen(term->output));
			}
			XFlush(term->display);
		}

		printf("lap\n");
	}
}
