/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_drawing_function_pointers.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:55:00 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/04 18:40:31 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

void	init_drawing_function_pointers(t_term *term) {
	int	i;

	i = 0;
	while (i < 256) {
		if (isprint((char)i))
			term->drawing_functions[i] = draw_printable;
		else if ((char)i == '\v')
			term->drawing_functions[i] = draw_vertical_tab;
		else if ((char)i == '\r')
			term->drawing_functions[i] = draw_carriage_return;
		else if ((char)i == '\n')
			term->drawing_functions[i] = draw_newline;
		else if ((char)i == '\x1b')
			term->drawing_functions[i] = parse_escape_code;
		else
			term->drawing_functions[i] = draw_nothing;
		i++;
	}
}
