/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <waltibee@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 01:44:54 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/05 07:50:57 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

int	main(void) {
	t_x11	x11;
	t_pty	pty;
	t_grid	grid;
	t_term	term;
	
	term.x11 = &x11;
	term.pty = &pty;
	term.grid = &grid;
	if (init_window(&x11) == 1)
		return (EXIT_FAILURE);
	init_pty(&pty);
	init_grid(&grid);
	term_runtime(&term, &x11, &pty, &grid);
	destroy_term(&x11);
	return (0);
}
