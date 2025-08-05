/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_funcs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:25:48 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/05 19:11:12 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_FUNCS_H
# define TERM_FUNCS_H

void	destroy_term(t_x11 *x11);

void	exit_term(t_pty *pty, t_x11 *x11);

int		fill_grid(t_pty *pty, t_grid *grid);

void	handle_keypress(t_x11 *x11, t_pty *pty);

void	init_grid(t_grid *grid);

void	init_pty(t_pty *pty);

int		init_window(t_x11 *x11);

void	redraw(t_term *term, t_x11 *x11, t_grid *grid);

void	term_runtime(t_term *term, t_x11 *x11, t_pty *pty, t_grid *grid);

void	grid_printable(t_grid *grid, char *buffer, int *i);
void	grid_vertical_tab(t_grid *grid, char *buffer, int *i);
void	grid_carriage_return(t_grid *grid, char *buffer, int *i);
void	grid_newline(t_grid *grid, char *buffer, int *i);
void	grid_tab(t_grid *grid, char *buffer, int *i);
void	grid_backspace(t_grid *grid, char *buffer, int *i);
void	grid_nothing(t_grid *grid, char *buffer, int *i);
void	parse_escape_code(t_grid *grid, char *buffer, int *i);

#endif
