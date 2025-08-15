/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:50:42 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/12 03:03:12 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pseudo_terminal.h"
#include "window.h"

void	handle_keypress(t_x11 *x11, t_pty *pty) {
	XKeyEvent	*kev;
	KeySym		keysym;
	char		buff[32];
	int			len;

	kev = &x11->event.xkey;
	keysym = XLookupKeysym(kev, 0);
	if ((kev->state & ControlMask) && (keysym == XK_c)) {
		write(pty->parent_fd, "\x03", 1);
		return ;
	}
	if ((kev->state & ControlMask) && (keysym == XK_d)) {
		write(pty->parent_fd, "\x04", 1);
		return ;
	}
	len = XLookupString(kev, buff, sizeof(buff), &keysym, NULL);
	if (len > 0 && isprint(buff[0])) {
		write(pty->parent_fd, buff, len);
	} else if (keysym == XK_Return) {
		write(pty->parent_fd, "\r", 1);
	} else if (keysym == XK_BackSpace) {
		write(pty->parent_fd, "\x7f", 1);
	} else if (keysym == XK_Tab) {
		write(pty->parent_fd, "\x09", 1);
	} else if (keysym == XK_Left) {
		write(pty->parent_fd, "\x1b[D", 3);
	} else if (keysym == XK_Right) {
		write(pty->parent_fd, "\x1b[C", 3);
	} else if (keysym == XK_Up) {
		write(pty->parent_fd, "\x1b[A", 3);
	} else if (keysym == XK_Down) {
		write(pty->parent_fd, "\x1b[B", 3);
	}
}
