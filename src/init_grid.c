/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:55:00 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/07 03:07:52 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "screen.h"

void	init_grid_function_pointers(t_grid *grid) {
	int	i;

	i = 0;
	while (i < 256) {
		if (isprint((char)i))
			grid->grid_functions[i] = grid_printable;
		else if ((char)i == '\v')
			grid->grid_functions[i] = grid_vertical_tab;
		else if ((char)i == '\r')
			grid->grid_functions[i] = grid_carriage_return;
		else if ((char)i == '\n')
			grid->grid_functions[i] = grid_newline;
		else if ((char)i == '\t')
			grid->grid_functions[i] = grid_tab;
		else if ((char)i == '\b')
			grid->grid_functions[i] = grid_backspace;
		else if ((char)i == '\x1b')
			grid->grid_functions[i] = parse_escape_code;
		else
			grid->grid_functions[i] = grid_nothing;
		i++;
	}
}

size_t	chunk_needed(t_grid *grid) {
	size_t	total_size;

	total_size = 0;
	total_size += (sizeof(char *) * grid->height);
	total_size += (sizeof(char) * grid->height * grid->width);
	total_size += (sizeof(int *) * grid->height * 2);
	total_size += (sizeof(int) * grid->height * grid->width * 2);
	return (total_size);
}

//this function will set all the pointers to addresses in the chunk so we have
//all the objects we need living inside that one chunk of memory.
void	create_storage(t_grid *grid) {
	void			*current;
	unsigned int	i;

	current = grid->chunk;
	grid->screen = current;
	current += (sizeof(char *) * grid->height);
	i = 0;
	while (i < grid->height) {
		grid->screen[i] = current;
		i++;
		current += (sizeof(char) * grid->width);
	}
	grid->fg_colors = current;
	current += (sizeof(int *) * grid->height);
	i = 0;
	while (i < grid->height) {
		grid->fg_colors[i] = current;
		i++;
		current += (sizeof(int) * grid->width);
	}
	grid->bg_colors = current;
	current += (sizeof(int *) * grid->height);
	i = 0;
	while (i < grid->height) {
		grid->bg_colors[i] = current;
		i++;
		current += (sizeof(int) * grid->width);
	}
}

void	zero_screen(t_grid *grid) {
	unsigned int	i;
	unsigned int	j;

	memset(grid->screen[0], ' ', sizeof(char) * grid->width * grid->height);
	memset(grid->bg_colors[0], 0, sizeof(int) * grid->width *grid->height);
	i = 0;
	while (i < grid->height) {
		j = 0;
		while (j < grid->width) {
			grid->fg_colors[i][j] = 0xFFFFFF;
			j++;
		}
		i++;
	}
}

//instead of allocating each object separately, we allocate one time one big
//chunk that is as big as we need it. the idea being it is less syscalls, less
//heap fragmentation, less occasion for malloc to fail,
//just one free at the end and maybe more cache efficiency but I am just 
//wanking at this point
//
//and also I fucking can and I want to try
int	init_grid(t_grid *grid) {
	grid->width = 80;
	grid->height = 25;
	grid->chunk = malloc(chunk_needed(grid));
	if (!grid->chunk)
		return (1);
	create_storage(grid);
	zero_screen(grid);
	grid->x = 0;
	grid->y = 0;
	grid->spaces_per_tab = 4;
	init_grid_function_pointers(grid);
	return (0);
}
