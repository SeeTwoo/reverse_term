/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:06:20 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/03 05:18:46 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_STRUCTS_H
# define TERM_STURCTS_H

typedef struct s_term	t_term;

struct s_term {
	Display		*display;
	Window		root;
	Window		win;
	int			screen;
	XEvent		event;
	Atom		wm_delete;
	GC			gc;
	XFontStruct	*font;
	int			parent_fd;
	char		output[256];
};

#endif
