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

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "window.h"
#include "pseudo_terminal.h"
#include "screen.h"
#include "terminal.h"

void	cursor_blink(t_x11 *x11, t_grid *grid);
void	cursor_blink_off(t_x11 *x11, t_grid *grid);
void	cursor_blink_on(t_x11 *x11, t_grid *grid);
void	exit_term(t_pty *pty, t_x11 *x11);
int		fill_grid(t_pty *pty, t_grid *grid);
void	handle_keypress(t_x11 *x11, t_pty *pty);
void	render(t_x11 *x11, t_grid *grid);
void	print_grid(t_grid *grid);

void	term_runtime(t_x11 *x11, t_pty *pty, t_grid *grid) {
	struct timeval	tv;
	struct winsize	ws;
	int				x_fd;
	int				max_fd;
	int				select_ret;
	fd_set			read_fds;

	ws.ws_row = grid->height;
	ws.ws_col = grid->width;
	ioctl(STDOUT_FILENO, TIOCSWINSZ, &ws);
	XMapWindow(x11->display, x11->win);
	x_fd = ConnectionNumber(x11->display);
	max_fd = (x_fd > pty->parent_fd ? x_fd : pty->parent_fd) + 1;
	x11->cursor_on = true;
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
			cursor_blink(x11, grid);
			continue ;
		}

		if (FD_ISSET(pty->parent_fd, &read_fds)) {
			cursor_blink_off(x11, grid);
			if (fill_grid(pty, grid) == 1)
				exit(EXIT_FAILURE);
			cursor_blink_on(x11, grid);
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
