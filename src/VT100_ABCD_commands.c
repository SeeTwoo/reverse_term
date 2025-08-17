/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   VT100_ABCD_commands.c                               :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                 +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "screen.h"

void	A_cursor_up(t_grid *grid, int *args, int ac) {
	if (ac == 0)
		args[0] = 1;
	grid->y--;
}

void	C_cursor_forward(t_grid *grid, int *args, int ac) {
	if (ac == 0)
		args[0] = 1;
	if (cursor_is_right(grid))
		return ;
	printf("hello from the C command\n");
	grid->x++;
}
