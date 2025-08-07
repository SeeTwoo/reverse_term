/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_render_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 02:23:01 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/07 00:46:16 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

void	new_render_op(t_grid *grid, int type, int x, int y) {
	grid->current_op->type = type;
	grid->current_op->x = x;
	grid->current_op->y = y;
	grid->current_op++; 
}
