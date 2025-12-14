/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:42:23 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/09 07:27:56 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

typedef struct s_fract	t_fract;

int		key_handler(int keysym, t_fract *fract);
int		mouse_handler(int btn, int x, int y, t_fract *fract);
int		exit_handler(t_fract *fract);
int		mouse_motion_handler(int x, int y, t_fract *fract);
int		button_release_handler(int btn, int x, int y, t_fract *fract);
void	recenter(t_fract *fract);
void	process_step(t_fract *fract, int step_inc);
void	process_zoom(t_fract *fract, double zoom_factor, int x, int y);
void	process_shift(t_fract *fract, double *val, double shift_amount);
void	re_color(t_fract *fract, int mode);
void	resize(t_fract *fract);
void	handle_threads(t_fract *fract);
void	show_help(t_fract *fract);
void	toggle_progressive_renderer(t_fract *fract);

#endif /* EVENTS_H */