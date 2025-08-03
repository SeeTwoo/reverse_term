/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_current_buffer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:54:24 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/03 21:46:17 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

#ifndef GREEN
# define GREEN "\e[032m"
# define RESET "\e[0m"
#endif

int	print_current_buffer(t_term *term) {
	int				i;
	char			*buff;
	unsigned char	c;

	i = 0;
	buff = term->output;
	while (buff[i])
	{
		c = buff[i];
		if (isprint(c))
			printf("%c", c);
		else
			printf("\\x%02x", c);
		i++;
	}
	printf("\n");
	return (0);
}
