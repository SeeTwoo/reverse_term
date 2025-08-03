/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_funcs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:25:48 by seetwoo           #+#    #+#             */
/*   Updated: 2025/08/03 14:20:38 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_FUNCS_H
# define TERM_FUNCS_H

void	handle_keypress(t_term *term);
int		init_window(t_term *term);
int		init_event(t_term *term);
void	destroy_term(t_term *term);
void	term_runtime(t_term *term);

#endif
