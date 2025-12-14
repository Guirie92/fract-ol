/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 04:18:38 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/12 19:50:22 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include "X11/X.h"
#include "X11/keysym.h"
#include <math.h>

void	recenter(t_fract *fract)
{
	fract->zoom = 1.0;
	if (fract->fract_mode == E_MANDELBROT)
		fract->sftx = -0.5;
	else
		fract->sftx = 0.0;
	fract->sfty = 0.0;
	fract->steps = STEPS;
	render(fract);
}

void	process_step(t_fract *fract, int step_inc)
{
	if (step_inc >= 0 && fract->steps <= STEPS_MAX - STEPS_INC)
	{
		fract->steps += STEPS_INC;
		render(fract);
	}
	else if (step_inc < 0 && fract->steps >= STEPS_INC)
	{
		fract->steps -= STEPS_INC;
		render(fract);
	}
}

void	process_shift(t_fract *fract, double *val, double shift_amount)
{
	(*val) += shift_amount;
	render(fract);
}

void	re_color(t_fract *fract, int mode)
{
	int	idx;

	if (mode == E_CLR_GRADIENT)
	{
		fract->clr_offset += 1;
		if (fract->clr_offset >= 256)
			fract->clr_offset = 0;
		fract->clr_bnd += 250;
		fract->clr_shift += 0.05;
		fract->clr_shift = fmod(fract->clr_shift, 1.0);
	}
	else if (mode == E_CLR_MODE)
	{
		if (fract->clr_mode == E_CLR_DEFAULT)
			fract->clr_mode = E_CLR_DEEP;
		else
			fract->clr_mode = E_CLR_DEFAULT;
		idx = (fract->fract_mode * NUM_COLOR_MODES) + fract->clr_mode;
		if (fract->threads.is_multithread == 1)
			fract->render_func = &trender_progressive;
		else
			fract->render_func = fract->rend_funcs[idx];
		fract->threads.worker_rend_func = fract->rend_funcs[idx + FUNC_BLOCK_S];
	}
	render(fract);
}

void	show_help(t_fract *fract)
{
	if (fract->info_panel_on)
	{
		render(fract);
		fract->info_panel_on = 0;
	}
	else
	{
		draw_help_panel(fract);
		fract->info_panel_on = 1;
	}
}
