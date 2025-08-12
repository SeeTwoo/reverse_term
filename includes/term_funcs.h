/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_funcs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:25:48 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/12 14:14:04 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_FUNCS_H
# define TERM_FUNCS_H

int		cursor_handling(t_x11 *x11, t_grid *grid);
int		cursor_blink_off(t_x11 *x11, t_grid *grid);
int		wipe_cursor(t_x11 *x11, int cursor_x, int cursor_y);

void	destroy_term(t_x11 *x11);

void	skip_to_args(char **buffer);
int		strtoi_index(char const *s, int *index);

void	exit_term(t_pty *pty, t_x11 *x11);

int		fill_grid(t_pty *pty, t_grid *grid);

void	print_raw_buffer(char *buffer);
int		get_output(t_pty *pty, char *buffer);

void	handle_keypress(t_x11 *x11, t_pty *pty);

void	init_grid(t_grid *grid);

void	init_pty(t_pty *pty);

int		init_window(t_x11 *x11);

void	new_render_op(t_grid *grid, int type, int x, int y);

void	render(t_x11 *x11, t_grid *grid);

void	term_runtime(t_x11 *x11, t_pty *pty, t_grid *grid);

void	grid_printable(t_grid *grid, char **buffer);
void	grid_vertical_tab(t_grid *grid, char **buffer);
void	grid_carriage_return(t_grid *grid, char **buffer);
void	grid_newline(t_grid *grid, char **buffer);
void	grid_tab(t_grid *grid, char **buffer);
void	grid_backspace(t_grid *grid, char **buffer);
void	grid_nothing(t_grid *grid, char **buffer);
void	parse_escape_code(t_grid *grid, char **buffer);

void	cursor_movement(t_grid *grid, int *args, int ac);
void	erase_display(t_grid *grid, int *args, int ac);
void	erase_line(t_grid *grid, int *args, int ac);

#endif
