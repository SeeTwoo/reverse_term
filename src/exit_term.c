/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:15:58 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/04 20:38:24 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_term.h"

void	exit_term(t_term *term) {
	kill(-term->shell_pid, SIGHUP);
	waitpid(term->shell_pid, NULL, 0);
	destroy_term(term);
	exit(EXIT_SUCCESS);
}
