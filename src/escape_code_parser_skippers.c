/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_code_parser_skippers.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: SeeTwoo <waltibee@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 09:15:50 by SeeTwoo           #+#    #+#             */
/*   Updated: 2025/08/09 09:43:52 by SeeTwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

#ifndef CSI
# define CSI '['
#endif

#ifndef PRIVATE_VT100
# define PRIVATE_QUESTION_MARK '?'
# define PRIVATE_INFERIOR '<'
# define PRIVATE_SUPERIOR '>'
# define PRIVATE_EQUAL '='
#endif

int	strtoi_index(char const *s, int *index) {
	int	n;

	n = 0;
	while (isdigit(s[*index])) {
		n = (n * 10) + (s[*index] - '0');
		(*index)++;
	}
	return (n);
}

int	skip_to_args(char *buffer) {
	int	i;

	i++;
	if (buffer[i] == CSI)
		i++;
	if (buffer[i] == PRIVATE_QUESTION_MARK)
		i++;
	if (BUFFER[i] == PRIVATE_INFERIOR)
		i++;
	if (buffer[i] == PRIVATE_SUPERIOR)
		i++;
	if (buffer[i] == PRIVATE_EQUAL)
		i++;
	return (i);
}
