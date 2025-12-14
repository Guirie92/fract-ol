/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:13:04 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/13 02:23:31 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "X11/keysym.h"
#include "X11/X.h"
#include <limits.h>

/*
 * Events queue up asynchronously. For instance, if each event (within a single
 * frame) takes 20 seconds to process and you press a key, say,
 * 3 times in quick succession, then the 3 events
 * will queue up and take (20 * 3 sec) 1 minute to fully process all of them,
 * each event taking 20 seconds to complete.
 */

int	exit_handler(t_fract *fract)
{
	free_res(fract, EXIT_FAILURE);
	return (0);
}

static inline void	check_keys_movement(int keysym, t_fract *fract)
{
	if (keysym == XK_Up)
		process_shift(fract, &fract->sfty, SHIFT_AMOUNT * fract->zoom);
	else if (keysym == XK_Down)
		process_shift(fract, &fract->sfty, -(SHIFT_AMOUNT * fract->zoom));
	else if (keysym == XK_Left)
		process_shift(fract, &fract->sftx, -(SHIFT_AMOUNT * fract->zoom));
	else if (keysym == XK_Right)
		process_shift(fract, &fract->sftx, SHIFT_AMOUNT * fract->zoom);
}

static inline void	check_keys_general(int keysym, t_fract *fract)
{
	if (keysym == XK_Escape)
		exit_handler(fract);
	else if (keysym == XK_plus || keysym == XK_KP_Add)
		process_step(fract, STEPS_INC);
	else if (keysym == XK_minus || keysym == XK_KP_Subtract)
		process_step(fract, -STEPS_INC);
	else if (keysym == XK_r || keysym == XK_R)
		recenter(fract);
	else if (keysym == XK_c || keysym == XK_C)
		re_color(fract, E_CLR_GRADIENT);
	else if (keysym == XK_v || keysym == XK_V)
		re_color(fract, E_CLR_MODE);
	else if (keysym == XK_f || keysym == XK_F)
		resize(fract);
	else if (keysym == XK_t || keysym == XK_T)
		handle_threads(fract);
	else if (keysym == XK_h || keysym == XK_H)
		show_help(fract);
	else if (keysym == XK_p || keysym == XK_P)
		toggle_progressive_renderer(fract);
	else if (keysym == XK_1 || keysym == XK_2 || keysym == XK_3)
		switch_fractals(keysym, fract);
}

int	key_handler(int keysym, t_fract *fract)
{
	check_keys_movement(keysym, fract);
	check_keys_general(keysym, fract);
	return (0);
}

void	toggle_progressive_renderer(t_fract *fract)
{
	if (fract->progressive_rend)
		fract->progressive_rend = 0;
	else
		fract->progressive_rend = 1;
}
