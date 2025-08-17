/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <waltibee@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 01:44:54 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/05 20:13:24 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "window.h"
#include "pseudo_terminal.h"
#include "screen.h"
#include "terminal.h"

int	main(void) {
	t_x11	x11;
	t_pty	pty;
	t_grid	grid;
	
//	setenv("TERM", "xterm-256color", 1);
	if (init_window(&x11) == 1)
		return (1);
	if (init_grid(&grid) == 1)
		return (1);
	init_pty(&pty);
	term_runtime(&x11, &pty, &grid);
	return (0);
}
