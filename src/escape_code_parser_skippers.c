/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_code_parser_skippers.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: SeeTwoo <waltibee@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 09:15:50 by SeeTwoo           #+#    #+#             */
/*   Updated: 2025/08/12 02:35:41 by seetwoo          ###   ########.fr       */
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

void	skip_to_args(char **buffer) {
//	print_raw_buffer(*buffer);
	if (**buffer == CSI)
		(*buffer)++;
	if (**buffer == PRIVATE_QUESTION_MARK)
		(*buffer)++;
	if (**buffer == PRIVATE_INFERIOR)
		(*buffer)++;
	if (**buffer == PRIVATE_SUPERIOR)
		(*buffer)++;
	if (**buffer == PRIVATE_EQUAL)
		(*buffer)++;
}
