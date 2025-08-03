/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:44:55 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/03 02:47:35 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

int	init_event(t_term *term)
{
	XSelectInput(term->display, term->win,
		ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask);
	term->wm_delete = XInternAtom(term->display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(term->display, term->win, &term->wm_delete, 1);
	return (SUCCESS);
}
