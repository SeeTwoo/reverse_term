/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 06:11:13 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/12 13:23:06 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "pseudo_terminal.h"
#include "screen.h"

void	scroll_grid_up(t_grid *grid) {
	unsigned int	y;

	y = 0;
	while (y < grid->height - 1) {
		memmove(grid->screen[y], grid->screen[y + 1], grid->width * sizeof(t_cell));
		y++;
	}
	memset(grid->screen[grid->height - 1], ' ', grid->width);
	grid->full_redraw = true;
	grid->x = 0;
}

void	grid_printable(t_grid *grid, char **buffer) {
	if (grid->x >= grid->width - 1 && grid->y < grid->height - 1) {
		grid->x = 0;
		grid->y++;
	} else if (grid->x >= grid->width - 1 && grid->y >= grid->height - 1) {
		scroll_grid_up(grid);
	}
	new_render_op(grid, PRINTABLE, grid->x, grid->y);
	grid->screen[grid->y][grid->x].c = **buffer;
	grid->x++;
	(*buffer)++;
}

void	grid_backspace(t_grid *grid, char **buffer) {
	grid->x--;
	(*buffer)++;
}

void	grid_vertical_tab(t_grid *grid, char **buffer) {
	if (grid->y >= grid->height - 1) {
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
	if (grid->y >= grid->height - 1) {
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
	if (grid->width - (grid->x + 1) < grid->spaces_per_tab && grid->y < grid->height - 1) {
		grid->y++;
		grid->x = 0;
		(*buffer)++;
		return ;
	} else if (grid->width - (grid->x + 1) < grid->spaces_per_tab && grid->y >= grid->height - 1) {
		scroll_grid_up(grid) ;
		(*buffer)++;
		return ;
	}
	new_render_op(grid, PRINTABLE, grid->x, grid->y);
	grid->screen[grid->y][grid->x].c = ' ';
	grid->x++;
	while (grid->x % grid->spaces_per_tab != 0) {
		new_render_op(grid, PRINTABLE, grid->x, grid->y);
		grid->screen[grid->y][grid->x].c = ' ';
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
		return (1);
	current = &buffer[0];
	bzero(grid->operations, sizeof(grid->operations));
	grid->current_op = grid->operations;
	while (*current) {
		grid->grid_functions[(unsigned char)*current](grid, &current);
	}
	grid->current_op->type = END_LIST;
	return (0);
}
