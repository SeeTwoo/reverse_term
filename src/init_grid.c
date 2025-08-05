/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:55:00 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/05 19:17:21 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

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

void	init_grid(t_grid *grid) {
	grid->x = 0;
	grid->y = 0;
	grid->x_draw = 0;
	grid->y_draw = 0;
	memset(grid->grid, ' ', 25 * 80);
	init_grid_function_pointers(grid);
}
