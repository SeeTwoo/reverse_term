/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   screen.h                                            :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                 +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCREEN_H
# define SCREEN_H

#include <stdbool.h>

typedef struct s_grid		t_grid;
typedef struct s_render_op	t_render_op;

typedef void				(*t_grid_function)(t_grid *grid, char **buffer);
typedef void				(*t_vt100_command)(t_grid *grid, int *args, int ac);

typedef enum {
	PRINTABLE,
	ERASE_DISPLAY,
	ERASE_LINE,
	DELETE_CHARACTER,
	END_LIST
} e_render_op_tye;

struct s_render_op {
	int	type;
	int	x;
	int y;
};

struct s_grid {
	void			*chunk;
	char			**screen;
	int				**fg_colors;
	int				**bg_colors;
	unsigned int	x;
	unsigned int	y;
	unsigned int	spaces_per_tab;
	unsigned int	width;
	unsigned int	height;
	bool			full_redraw;
	t_grid_function	grid_functions[256];
	t_vt100_command	command_functions[58];
	t_render_op		operations[4096];
	t_render_op		*current_op;
};

//int		fill_grid(t_pty *pty, t_grid *grid);
int		init_grid(t_grid *grid);
void	skip_to_args(char **buffer);

void	A_cursor_up(t_grid *grid, int *args, int ac);
void	C_cursor_forward(t_grid *grid, int *args, int ac);
void	H_cursor_movement(t_grid *grid, int *args, int ac);
void	J_erase_display(t_grid *grid, int *args, int ac);
void	K_erase_line(t_grid *grid, int *args, int ac);
void	P_delete_character(t_grid *grid, int *args, int ac);
void	command_nothing(t_grid *grid, int *args, int ac);

void	new_render_op(t_grid *grid, int type, int x, int y);

int		cursor_is_right(t_grid *grid);
int		cursor_is_left(t_grid *grid);
int		cursor_is_down(t_grid *grid);

void	grid_printable(t_grid *grid, char **buffer);
void	grid_vertical_tab(t_grid *grid, char **buffer);
void	grid_carriage_return(t_grid *grid, char **buffer);
void	grid_newline(t_grid *grid, char **buffer);
void	grid_tab(t_grid *grid, char **buffer);
void	grid_backspace(t_grid *grid, char **buffer);
void	grid_nothing(t_grid *grid, char **buffer);
void	parse_escape_code(t_grid *grid, char **buffer);

#endif
