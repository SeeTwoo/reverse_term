/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:06:20 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/04 20:13:43 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_STRUCTS_H
# define TERM_STURCTS_H

typedef struct s_term	t_term;
typedef struct s_draw	t_draw;
typedef void			(*t_drawing_function)(t_term *term, t_draw *draw);

struct s_term {
	pid_t				shell_pid;
	Display				*display;
	Window				root;
	Window				win;
	int					screen;
	XEvent				event;
	Atom				wm_delete;
	GC					gc;
	XFontStruct			*font;
	int					parent_fd;
	char				output[1024];
	size_t				out_len;
	t_drawing_function	drawing_functions[256];
};

struct s_draw {
	int		i;
	int		x;
	int		y;
	int		line_height;
	int		character_width;
	size_t	line_len;
};

#endif
