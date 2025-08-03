/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <waltibee@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 01:44:54 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/03 03:13:11 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

int	main(void) {
	t_term	term;
	
	if (init_window(&term) == 1)
		return (EXIT_FAILURE);
	init_event(&term);
	XMapWindow(term.display, term.win);
	XFlush(term.display);
	while (1) {
		XNextEvent(term.display, &term.event);
		if (term.event.type == ClientMessage && (Atom)term.event.xclient.data.l[0] == term.wm_delete)
			break ;
		if (term.event.type == KeyPress || term.event.type == ButtonPress)
			break ;
	}
	destroy_term(&term);
	return (0);
}
