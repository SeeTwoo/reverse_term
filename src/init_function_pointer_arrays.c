/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   init_function_pointer_arrays.c                      :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                 +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>

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

void	init_vt100_command_function_pointers(t_grid *grid) {
	int	i;

	i = 0;
	while (i < 58) {
		if (i + 'A' == 'A')
			grid->command_functions[i] = A_cursor_up;
		else if (i + 'A' == 'C')
			grid->command_functions[i] = C_cursor_forward;
		else if (i + 'A' == 'H')
			grid->command_functions[i] = H_cursor_movement;
		else if (i + 'A' == 'J')
			grid->command_functions[i] = J_erase_display;
		else if (i + 'A' == 'K')
			grid->command_functions[i] = K_erase_line;
		else if (i + 'A' == 'P')
			grid->command_functions[i] = P_delete_character;
		else
			grid->command_functions[i] = command_nothing;
		i++;
	}
}

void	init_render_operations_function_pointers(t_grid *grid) {
	grid->render_operation_functions[PRINTABLE] = render_printable;
	grid->render_operation_functions[ERASE_DISPLAY] = full_redraw;
	grid->render_operation_functions[ERASE_LINE] = render_line_erasing;
	grid->render_operation_functions[DELETE_CHARACTER] = render_character_deletion;
}
