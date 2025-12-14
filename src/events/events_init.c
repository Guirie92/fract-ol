/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 02:22:04 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/13 02:23:58 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "X11/keysym.h"
#include "X11/X.h"

void	events_init(t_fract *fract)
{
	int	idx;

	fract->sftx = 0.0;
	if (fract->fract_mode == E_MANDELBROT)
		fract->sftx = -0.5;
	idx = (fract->fract_mode * NUM_COLOR_MODES) + fract->clr_mode;
	fract->render_func = fract->rend_funcs[idx];
	fract->threads.worker_rend_func = fract->rend_funcs[idx + FUNC_BLOCK_S];
	mlx_hook(fract->mlx_win, KeyPress, KeyPressMask, &key_handler, fract);
	mlx_hook(fract->mlx_win, ButtonPress, ButtonPressMask,
		&mouse_handler, fract);
	mlx_hook(fract->mlx_win, DestroyNotify, StructureNotifyMask,
		&exit_handler, fract);
	mlx_hook(fract->mlx_win, ButtonRelease, ButtonReleaseMask,
		&button_release_handler, fract);
	mlx_hook(fract->mlx_win, MotionNotify, PointerMotionMask,
		&mouse_motion_handler, fract);
	progressive_reset(fract);
	mlx_loop_hook(fract->mlx, &progressive_tick, fract);
}
