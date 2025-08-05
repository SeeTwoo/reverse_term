/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:06:20 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/05 08:07:43 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_STRUCTS_H
# define TERM_STURCTS_H

typedef struct s_term		t_term;
typedef struct s_x11		t_x11;
typedef struct s_pty		t_pty;
typedef struct s_grid		t_grid;

typedef struct s_draw		t_draw;

typedef void				(*t_grid_function)(t_grid *grid, char *buffer, int *i);

struct s_x11 {
	Display				*display;
	Window				root;
	Window				win;
	int					screen;
	XEvent				event;
	Atom				wm_delete;
	GC					gc;
	XFontStruct			*font;
};

struct s_pty {
	pid_t				shell_pid;
	int					parent_fd;
};

struct s_grid {
	char			grid[25][80];
	int				x;
	int				y;
	t_grid_function	grid_functions[256];
};

struct s_term {
	t_x11	*x11;
	t_pty	*pty;
	t_grid	*grid;
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
