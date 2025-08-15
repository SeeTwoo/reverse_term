/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pty.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 06:58:37 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/05 08:14:25 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "pseudo_terminal.h"

void	launch_shell(void) {
	execlp("/bin/bash", "bash", "--posix", NULL);
	exit(EXIT_FAILURE);
}

void	init_pty(t_pty *pty) {
	pty->shell_pid = forkpty(&pty->parent_fd, NULL, NULL, NULL);
	if (pty->shell_pid == 0)
		launch_shell();
}
