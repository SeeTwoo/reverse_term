/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 02:14:38 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/07 09:21:00 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

void	print_raw_buffer(char *buffer) {
	int	i;

	i = 0;
	printf("\x1b[31mprinting buffer\n\x1b[0m");
	while (buffer[i]) {
		if (isprint(buffer[i]))
			printf("%c", buffer[i]);
		else
			printf("\\x%02x", buffer[i]);
		i++;
	}
	printf("\n");
}

//to replace with something along the line of get next line that could handle
//something arbitraryly large
int	get_output(t_pty *pty, char *buffer) {
	int	bytes_read;

	bytes_read = read(pty->parent_fd, buffer, 1023);
	if (bytes_read <= 0)
		return (bytes_read);
	buffer[bytes_read] = '\0';
//	print_raw_buffer(buffer);
	return (bytes_read);
}
