/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 06:11:13 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/06 22:48:26 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

void	scroll_grid_up(t_grid *grid) {
	int	y;

	y = 0;
	while (y < GRID_H - 1) {
		memmove(grid->grid[y], grid->grid[y + 1], GRID_W);
		y++;
	}
	memset(grid->grid[GRID_H - 1], ' ', GRID_W);
	grid->full_redraw = true;
	grid->x = 0;
}

int	grid_printable(t_grid *grid, char *buffer) {
	if (grid->x >= GRID_W - 1 && grid->y < GRID_H - 1) {
		grid->x = 0;
		grid->y++;
	} else if (grid->x >= GRID_W - 1 && grid->y >= GRID_H - 1) {
		scroll_grid_up(grid);
	}
	new_render_op(grid, PRINTABLE, grid->x, grid->y);
	grid->grid[grid->y][grid->x] = *buffer;
	grid->x++;
	return (1);
}

int	grid_backspace(t_grid *grid, char *buffer) {
	(void)buffer;
	grid->x--;
	grid->grid[grid->y][grid->x] = ' ';
	new_render_op(grid, BACKSPACE, grid->x, grid->y);
	return (1);
}

int	grid_vertical_tab(t_grid *grid, char *buffer) {
	(void)buffer;
	if (grid->y >= GRID_H - 1) {
		scroll_grid_up(grid);
		return (1);
	}
	grid->y++;
	return (1);
}	

int	grid_carriage_return(t_grid *grid, char *buffer) {
	(void)buffer;
	grid->x = 0;
	return (1);
}

int	grid_newline(t_grid *grid, char *buffer) {
	(void)buffer;
	if (grid->y >= GRID_H - 1) {
		scroll_grid_up(grid);
		grid->x = 0;
		return (1);
	}
	grid->y++;
	grid->x = 0;
	return (1);
}

int	grid_tab(t_grid *grid, char *buffer) {
	(void)buffer;
	if (GRID_W - (grid->x + 1) < SPACES_PER_TAB && grid->y < GRID_H - 1) {
		grid->y++;
		grid->x = 0;
		return (1);
	} else if (GRID_W - (grid->x + 1) < SPACES_PER_TAB && grid->y >= GRID_H - 1) {
		scroll_grid_up(grid) ;
		return (1);
	}
	new_render_op(grid, PRINTABLE, grid->x, grid->y);
	grid->grid[grid->y][grid->x] = ' ';
	grid->x++;
	while (grid->x % SPACES_PER_TAB != 0) {
		new_render_op(grid, PRINTABLE, grid->x, grid->y);
		grid->grid[grid->y][grid->x] = ' ';
		grid->x++;
	}
	return (1);
}

int	parse_escape_code(t_grid *grid, char *buffer) {
	int	i;

	(void)grid;
	i = 0;
	while (buffer[i] && !isalpha(buffer[i]))
		i++;
	if (buffer[i])
		i++;
	return (i);
}

int	grid_nothing(t_grid *grid, char *buffer) {
	(void)grid;
	(void)buffer;
	return (1);
}

int	fill_grid(t_pty *pty, t_grid *grid) {
	char	buffer[1024];
	int		i;
	
	if (get_output(pty, buffer) <= 0)
		return (FAILURE);
	i = 0;
	bzero(grid->operations, sizeof(grid->operations));
	grid->current_op = grid->operations;
	while (buffer[i])
		i += grid->grid_functions[(int)buffer[i]](grid, &buffer[i]);
	grid->current_op->type = END_LIST;
	return (SUCCESS);
}
