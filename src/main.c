/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <waltibee@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 01:44:54 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/03 03:26:19 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

int	main(void) {
	t_term	term;
	
	if (init_window(&term) == 1)
		return (EXIT_FAILURE);
	init_event(&term);
	term_runtime(&term);
	destroy_term(&term);
	return (0);
}
