/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_mouse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 04:18:38 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/16 15:14:53 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "X11/keysym.h"
#include "X11/X.h"

void	process_zoom(t_fract *fract, double zoom_factor, int x, int y)
{
	double	mouse_x;
	double	mouse_y;
	double	coord_x;
	double	coord_y;

	coord_x = (x * fract->scl.sfw + fract->scl.offsetw);
	coord_y = (y * fract->scl.sfh + fract->scl.offseth);
	mouse_x = fract->sftx + coord_x * fract->zoom;
	mouse_y = fract->sfty + coord_y * fract->zoom;
	fract->zoom *= zoom_factor;
	fract->sftx = mouse_x - coord_x * fract->zoom;
	fract->sfty = mouse_y - coord_y * fract->zoom;
	render(fract);
}

static void	calc_fract_coordinates(int x, int y, t_fract *fract)
{
	double	coord_x_scaled;
	double	coord_y_scaled;

	if (fract->fract_mode == E_JULIA)
		return ;
	coord_x_scaled = (double)x * fract->scl.sfw + fract->scl.offsetw;
	coord_y_scaled = (double)y * fract->scl.sfh + fract->scl.offseth;
	fract->julia_r = fract->sftx + coord_x_scaled * fract->zoom;
	fract->julia_i = fract->sfty + coord_y_scaled * fract->zoom;
}

/*
 * Button4 (scroll-up)   -> Zoom in
 * Button5 (scroll-down) -> Zoom out
 */
int	mouse_handler(int btn, int x, int y, t_fract *fract)
{
	if (btn == Button1)
	{
		fract->is_panning = 1;
		fract->last_x = x;
		fract->last_y = y;
	}
	else if (btn == Button3)
	{
		if (fract->fract_mode != E_JULIA)
			calc_fract_coordinates(x, y, fract);
		switch_fractals(XK_2, fract);
	}
	else if (btn == Button4)
		process_zoom(fract, 1 - ZOOM_AMOUNT, x, y);
	else if (btn == Button5)
		process_zoom(fract, 1 + ZOOM_AMOUNT, x, y);
	return (0);
}

int	button_release_handler(int btn, int x, int y, t_fract *fract)
{
	(void)x;
	(void)y;
	if (btn == Button1)
		fract->is_panning = 0;
	return (0);
}

int	mouse_motion_handler(int x, int y, t_fract *fract)
{
	int		dx_pixels;
	int		dy_pixels;
	double	dx_complex;
	double	dy_complex;

	if (fract->is_panning == 1)
	{
		dx_pixels = x - fract->last_x;
		dy_pixels = y - fract->last_y;
		dx_complex = dx_pixels * fract->scl.sfw * fract->zoom;
		dy_complex = dy_pixels * fract->scl.sfh * fract->zoom;
		fract->sftx -= dx_complex;
		fract->sfty -= dy_complex;
		fract->last_x = x;
		fract->last_y = y;
		render(fract);
	}
	else
	{
		calc_fract_coordinates(x, y, fract);
		draw_julia_coords(fract);
		if (fract->fract_mode == E_JULIA_PREVIEW)
		{
			render(fract);
		}
	}
	return (0);
}
