/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   render_operations.h                                 :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                 +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_OPERATIONS_H
# define RENDER_OPERATIONS_H

typedef void				(t_render_function)(t_x11 *x11, t_grid *grid);

typedef struct s_render_op	t_render_op

typedef enum {
	PRINTABLE,
	ERASE_DISPLAY,
	ERASE_LINE,
	END_LIST
} e_render_op_tye;

struct s_render_op {
	int	type;
	int	x;
	int y;
};

void	cursor_movement(t_grid *grid, int *args, int ac);
void	erase_display(t_grid *grid, int *args, int ac);
void	erase_line(t_grid *grid, int *args, int ac);

void	new_render_op(t_grid *grid, int type, int x, int y);

#endif
