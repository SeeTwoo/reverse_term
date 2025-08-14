/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:15:58 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/05 07:25:26 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "window.h"
#include "pty.h"

void	exit_term(t_pty *pty, t_x11 *x11) {
	kill(-pty->shell_pid, SIGHUP);
	waitpid(pty->shell_pid, NULL, 0);
	destroy_term(x11);
	exit(EXIT_SUCCESS);
}
