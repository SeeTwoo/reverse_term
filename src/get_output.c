/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 02:14:38 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/06 23:19:02 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

//to replace with something along the line of get next line that could handle
//something arbitraryly large
int	get_output(t_pty *pty, char *buffer) {
	int	bytes_read;

	bytes_read = read(pty->parent_fd, buffer, 1023);
	if (bytes_read <= 0)
		return (bytes_read);
	buffer[bytes_read] = '\0';
	printf("%s\n\n", buffer);
	return (bytes_read);
}
