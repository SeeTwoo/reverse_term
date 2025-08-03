/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <waltibee@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 01:44:54 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/03 02:31:12 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

int	main(void) {
	t_term	term;
	
	if (init_window(&term) == 1)
		return (1);
	XSelectInput(
		term.display, term.win,
		ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask
	);
	term.wm_delete = XInternAtom(term.display, "WM_DELETE_WINDEW", False);
	XSetWMProtocols(term.display, term.win, &term.wm_delete, 1);
	XMapWindow(term.display, term.win);
	XFlush(term.display);
	while (1) {
		XNextEvent(term.display, &term.event);
		if (term.event.type == ClientMessage && (Atom)term.event.xclient.data.l[0] == term.wm_delete)
			break ;
		if (term.event.type == KeyPress || term.event.type == ButtonPress)
			break ;
	}
	XDestroyWindow(term.display, term.win);
	XCloseDisplay(term.display);
	return (0);
}
