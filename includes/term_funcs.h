/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_funcs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:25:48 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/04 18:46:11 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_FUNCS_H
# define TERM_FUNCS_H

void	handle_keypress(t_term *term);
int		init_window(t_term *term);
int		init_event(t_term *term);
void	destroy_term(t_term *term);
int		print_current_buffer(t_term *term);
void	redraw(t_term *term);
void	term_runtime(t_term *term);

void	init_drawing_function_pointers(t_term *term);
void	draw_printable(t_term *term, t_draw *draw);
void	draw_vertical_tab(t_term *term, t_draw *draw);
void	draw_carriage_return(t_term *term, t_draw *draw);
void	draw_newline(t_term *term, t_draw *draw);
void	parse_escape_code(t_term *term, t_draw *draw);
void	draw_nothing(t_term *term, t_draw *draw);

#endif
