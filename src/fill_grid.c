/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 06:11:13 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/05 18:15:52 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

void	scroll_grid_up(t_grid *grid, char *buffer, int *i) {
	int	y;

	(void)buffer;
	(void)i;
	y = 0;
	while (y < 24) {
		memmove(grid->grid[y], grid->grid[y + 1], 80);
		y++;
	}
	memset(grid->grid[24], ' ', 80);
}

void	grid_printable(t_grid *grid, char *buffer, int *i) {
	grid->grid[grid->y][grid->x] = buffer[*i];
	if (grid->x == 79) {
		grid_newline(grid, buffer, i);
	} else {
		grid->x++;
	}
	(*i)++;
}

void	grid_backspace(t_grid *grid, char *buffer, int *i) {
	(void)buffer;
	grid->x--;
	grid->grid[grid->y][grid->x] = ' ';
	(*i)++;
}

void	grid_vertical_tab(t_grid *grid, char *buffer, int *i) {
	(void)buffer;
	if (grid->y == 24) {
		scroll_grid_up(grid, buffer, i);
		(*i)++;
		return ;
	}
	grid->y++;
	(*i)++;
}	

void	grid_carriage_return(t_grid *grid, char *buffer, int *i) {
	(void)buffer;
	grid->x = 0;
	(*i)++;
}

void	grid_newline(t_grid *grid, char *buffer, int *i) {
	(void)buffer;
	if (grid->y == 24) {
		scroll_grid_up(grid, buffer, i);
		(*i)++;
		grid->x = 0;
		return ;
	}
	grid->y++;
	grid->x = 0;
	(*i)++;
}

void	grid_tab(t_grid *grid, char *buffer, int *i) {
	(void)buffer;
	grid->x += SPACES_PER_TAB - (grid->x % SPACES_PER_TAB);
	(*i)++;
}

void	parse_escape_code(t_grid *grid, char *buffer, int *i) {
	(void)grid;
	while (buffer[*i] && !isalpha(buffer[*i]))
		(*i)++;
	if (buffer[*i])
		(*i)++;
}

void	grid_nothing(t_grid *grid, char *buffer, int *i) {
	(void)grid;
	(void)buffer;
	(*i)++;
}

//to replace with something along the line of get next line that could handle
//something arbitraryly large
int	get_output(t_pty *pty, char *buffer) {
	int	bytes_read;

	bytes_read = read(pty->parent_fd, buffer, 1023);
	if (bytes_read <= 0)
		return (bytes_read);
	buffer[bytes_read] = '\0';
	return (bytes_read);
}

int	fill_grid(t_pty *pty, t_grid *grid) {
	char	buffer[1024];
	int		i;
	
	if (get_output(pty, buffer) <= 0)
		return (FAILURE);
	i = 0;
	while (buffer[i]) {
		if (!grid->grid_functions[(int)buffer[i]]) {
			printf("c = %c (\\x%02x\n", buffer[i], (int)buffer[i]);
			exit(EXIT_FAILURE);
		}
		grid->grid_functions[(int)buffer[i]](grid, buffer, &i);
	}
	return (SUCCESS);
}
