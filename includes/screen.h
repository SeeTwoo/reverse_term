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

typedef struct s_cell		t_cell;
typedef struct s_grid		t_grid;

typedef void				(*t_grid_function)(t_grid *grid, char **buffer);

struct s_cell {
	char	c;
	int		foreground_color;
	int		background_color;
	bool	bold;
};

struct s_grid {
	t_cell			**screen;
	unsigned int	x;
	unsigned int	y;
	unsigned int	spaces_per_tab;
	unsigned int	width;
	unsigned int	height;
	bool			full_redraw;
	t_grid_function	grid_functions[256];
	t_render_op		operations[4096];
	t_render_op		*current_op;
};

void	grid_printable(t_grid *grid, char **buffer);
void	grid_vertical_tab(t_grid *grid, char **buffer);
void	grid_carriage_return(t_grid *grid, char **buffer);
void	grid_newline(t_grid *grid, char **buffer);
void	grid_tab(t_grid *grid, char **buffer);
void	grid_backspace(t_grid *grid, char **buffer);
void	grid_nothing(t_grid *grid, char **buffer);
void	parse_escape_code(t_grid *grid, char **buffer);

#endif
