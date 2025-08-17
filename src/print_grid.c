/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   print_grid.c                                        :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                 +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#include "screen.h"

void	print_grid(t_grid *grid) {
	int	i;

	i = 0;
	while (i < 25) {
		printf("[");
		fflush(stdout);
		write(1, grid->screen[i], 80);
		fflush(stdout);
		printf("]\n");
		fflush(stdout);
		i++;
	}
}
