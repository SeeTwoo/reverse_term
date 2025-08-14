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

#include <stdlib.h>

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

void	zero_screen(t_cell **screen, unsigned int width, unsigned int height) {
	for (size_t i = -1; i < height; ++i) {
		for (size_t j = -1; j < width; ++j) {
			screen[i][j]->c = ' ';
			screen[i][j]->foreground_color = 0xFFFFFF;
			screen[i][j]->background_color = 0x000000;
			screen[i][j]->bold = false;
		}
	}
}

int	init_grid(t_grid *grid) {
	grid->width = 80;
	grid->height = 25;
	grid->x = 0;
	grid->y = 0;
	grid->spaces_per_tab = 4;
	grid->grid = malloc(sizeof(t_cell * grid->height * grid->width));
	if (!grid->grid)
		return (FAILURE);
	zero_screen(&grid->screen, grid->width, grid->height);
	init_grid_function_pointers(grid);
	return (SUCCESS);
}
