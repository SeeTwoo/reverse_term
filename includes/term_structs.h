/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:06:20 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/07 00:11:56 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_STRUCTS_H
# define TERM_STURCTS_H

typedef struct s_x11		t_x11;
typedef struct s_pty		t_pty;
typedef struct s_grid		t_grid;
typedef struct s_render_op	t_render_op;

typedef int					(*t_grid_function)(t_grid *grid, char *buffer);
typedef void				(t_render_function)(t_x11 *x11, t_grid *grid);

struct s_x11 {
	Display		*display;
	Window		root;
	Window		win;
	int			screen;
	XEvent		event;
	Atom		wm_delete;
	GC			gc;
	XFontStruct	*font;
	int			tile_height;
	int			tile_width;
	bool		cursor_blink;
};

struct s_pty {
	pid_t				shell_pid;
	int					parent_fd;
};

typedef enum {
	PRINTABLE,
	BACKSPACE,
	END_LIST
} e_render_op_tye;

struct s_render_op {
	int	type;
	int	x;
	int y;
};

struct s_grid {
	char			grid[25][80];
	int				x;
	int				y;
	bool			full_redraw;
	t_grid_function	grid_functions[256];
	t_render_op		operations[4096];
	t_render_op		*current_op;
};

#endif
