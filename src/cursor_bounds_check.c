/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   cursor_bounds_check.c                               :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                 +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "screen.h"

int	cursor_is_left(t_grid *grid) {
	return (grid->x == grid->width - 1);
}

int	cursor_is_right(t_grid *grid) {
	return (grid->x == 0);
}

int	cursor_is_down(t_grid *grid) {
	return (grid->y == grid->height - 1);
}
