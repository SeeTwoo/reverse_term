/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 06:11:13 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/12 02:31:49 by seetwoo          ###   ########.fr       */
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

void	grid_printable(t_grid *grid, char **buffer) {
	if (grid->x >= GRID_W - 1 && grid->y < GRID_H - 1) {
		grid->x = 0;
		grid->y++;
	} else if (grid->x >= GRID_W - 1 && grid->y >= GRID_H - 1) {
		scroll_grid_up(grid);
	}
	new_render_op(grid, PRINTABLE, grid->x, grid->y);
	grid->grid[grid->y][grid->x] = **buffer;
	grid->x++;
	(*buffer)++;
}

void	grid_backspace(t_grid *grid, char **buffer) {
	grid->x--;
	grid->grid[grid->y][grid->x] = ' ';
	new_render_op(grid, BACKSPACE, grid->x, grid->y);
	(*buffer)++;
}

void	grid_vertical_tab(t_grid *grid, char **buffer) {
	if (grid->y >= GRID_H - 1) {
		scroll_grid_up(grid);
		(*buffer)++;
		return ;
	}
	grid->y++;
	(*buffer)++;
}	

void	grid_carriage_return(t_grid *grid, char **buffer) {
	grid->x = 0;
	(*buffer)++;
}

void	grid_newline(t_grid *grid, char **buffer) {
	if (grid->y >= GRID_H - 1) {
		scroll_grid_up(grid);
		grid->x = 0;
		(*buffer)++;
		return ;
	}
	grid->y++;
	grid->x = 0;
	(*buffer)++;
}

void	grid_tab(t_grid *grid, char **buffer) {
	if (GRID_W - (grid->x + 1) < SPACES_PER_TAB && grid->y < GRID_H - 1) {
		grid->y++;
		grid->x = 0;
		(*buffer)++;
		return ;
	} else if (GRID_W - (grid->x + 1) < SPACES_PER_TAB && grid->y >= GRID_H - 1) {
		scroll_grid_up(grid) ;
		(*buffer)++;
		return ;
	}
	new_render_op(grid, PRINTABLE, grid->x, grid->y);
	grid->grid[grid->y][grid->x] = ' ';
	grid->x++;
	while (grid->x % SPACES_PER_TAB != 0) {
		new_render_op(grid, PRINTABLE, grid->x, grid->y);
		grid->grid[grid->y][grid->x] = ' ';
		grid->x++;
	}
	(*buffer)++;
}

void	grid_nothing(t_grid *grid, char **buffer) {
	(void)grid;
	(*buffer)++;
}

int	fill_grid(t_pty *pty, t_grid *grid) {
	char	buffer[1024];
	char	*current;
	
	if (get_output(pty, buffer) <= 0)
		return (FAILURE);
	current = &buffer[0];
	bzero(grid->operations, sizeof(grid->operations));
	grid->current_op = grid->operations;
	while (*current) {
		grid->grid_functions[(unsigned char)*current](grid, &current);
	}
	grid->current_op->type = END_LIST;
	return (SUCCESS);
}
