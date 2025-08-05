/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:50:42 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/05 07:31:47 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

void	handle_keypress(t_x11 *x11, t_pty *pty) {
	XKeyEvent	*kev;
	KeySym		keysym;
	char		buff[32];
	int			len;

	kev = &x11->event.xkey;
	keysym = XLookupKeysym(kev, 0);
	len = XLookupString(kev, buff, sizeof(buff), &keysym, NULL);
	if (len > 0 && isprint(buff[0])) {
		write(pty->parent_fd, buff, len);
	} else if (keysym == XK_Return) {
		write(pty->parent_fd, "\r", 1);
	} else if (keysym == XK_BackSpace) {
		write(pty->parent_fd, "\x7f", 1);
	}
}
