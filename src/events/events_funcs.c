/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:49:36 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/17 02:16:58 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "X11/keysym.h"
#include "X11/X.h"
#include <limits.h>

static void	reboot(t_fract *fract)
{
	if (fract->mlx && fract->img.img)
		mlx_destroy_image(fract->mlx, fract->img.img);
	if (fract->mlx && fract->jimg.img)
		mlx_destroy_image(fract->mlx, fract->jimg.img);
	if (fract->mlx && fract->mlx_win)
		mlx_destroy_window(fract->mlx, fract->mlx_win);
	fract->mlx_win = mlx_new_window(fract->mlx, fract->win_width,
			fract->win_height, fract->name);
	if (!fract->mlx_win)
		free_res(fract, EXIT_FAILURE);
	fract->img.img = mlx_new_image(fract->mlx, fract->win_width,
			fract->win_height);
	if (!fract->img.img)
		free_res(fract, EXIT_FAILURE);
	fract->img.addr = mlx_get_data_addr(fract->img.img, &fract->img.bpp,
			&fract->img.line_len, &fract->img.endian);
	fract->jimg.img = mlx_new_image(fract->mlx, fract->j_preview_width,
			fract->j_preview_height);
	if (!fract->jimg.img)
		free_res(fract, EXIT_FAILURE);
	fract->jimg.addr = mlx_get_data_addr(fract->jimg.img, &fract->jimg.bpp,
			&fract->jimg.line_len, &fract->jimg.endian);
	compute_pix_to_fract_scale(fract);
	fract->esc_val = (MANDELBROT_RANGE_MAX * MANDELBROT_RANGE_MAX);
	fract->steps = STEPS;
	fract->inv_max = 1.0f / fract->steps;
	fract->last_x = 0.0;
	fract->last_y = 0.0;
	fract->ren.total_blocks = 0;
	fract->ren.comp_blocks = 0;
	if (render_init(fract) == E_MEM_ERROR)
		free_res(fract, EXIT_FAILURE);
}

static void	events_rehook(t_fract *fract)
{
	fract->sftx = 0.0;
	if (fract->fract_mode == E_MANDELBROT)
		fract->sftx = -0.5;
	mlx_hook(fract->mlx_win, KeyPress, KeyPressMask, &key_handler, fract);
	mlx_hook(fract->mlx_win, ButtonPress, ButtonPressMask,
		&mouse_handler, fract);
	mlx_hook(fract->mlx_win, DestroyNotify, StructureNotifyMask,
		&exit_handler, fract);
	mlx_hook(fract->mlx_win, ButtonRelease, ButtonReleaseMask,
		&button_release_handler, fract);
	mlx_hook(fract->mlx_win, MotionNotify,
		PointerMotionMask | Button1MotionMask | ButtonMotionMask,
		&mouse_motion_handler, fract);
	//progressive_reset(fract);
}

void	resize(t_fract *fract)
{
	if (fract->screenres == E_DEFAULT)
	{
		fract->screenres = E_2K;
		fract->win_width = WIDTH_2K;
		fract->win_height = HEIGHT_2K;
		fract->j_preview_width = PANEL_JP_WIDTH_2K;
		fract->j_preview_height = PANEL_JP_HEIGHT_2K;
	}
	else if (fract->screenres == E_2K)
	{
		fract->screenres = E_4K;
		fract->win_width = WIDTH_4K;
		fract->win_height = HEIGHT_4K;
		fract->j_preview_width = PANEL_JP_WIDTH_4K;
		fract->j_preview_height = PANEL_JP_HEIGHT_4K;
	}
	else if (fract->screenres == E_4K)
	{
		fract->screenres = E_DEFAULT;
		fract->win_width = WIDTH;
		fract->win_height = HEIGHT;
		fract->j_preview_width = PANEL_JP_WIDTH;
		fract->j_preview_height = PANEL_JP_HEIGHT;
	}
	compute_padding(fract);
	reboot(fract);
	render(fract);
	events_rehook(fract);
	mlx_loop(fract->mlx);
}

void	handle_threads(t_fract *fract)
{
	int	idx;

	if (fract->threads.num_active_threads == 0)
		thread_init_pool(fract);
	if (fract->threads.is_multithread == 0)
	{
		fract->render_func = &trender_progressive;
		idx = (fract->fract_mode * NUM_COLOR_MODES)
			+ fract->clr_mode + FUNC_BLOCK_S;
		fract->threads.worker_rend_func = fract->rend_funcs[idx];
		fract->threads.is_multithread = 1;
		if (fract->fract_mode == E_MANDELBROT_JULIA_PREVIEW)
		{
			fract->render_func = &trender_progressive_julia_preview;
			fract->threads.worker_rend_func = &worker_mandelbrot_julia_preview;

		}
		else if (fract->fract_mode == E_BURNING_JULIA_PREVIEW)
		{
			fract->render_func = &trender_progressive_julia_preview;
			fract->threads.worker_rend_func = &worker_burning_julia_preview;
		}
	}
	else
	{
		idx = (fract->fract_mode * NUM_COLOR_MODES) + fract->clr_mode;
		fract->render_func = fract->rend_funcs[idx];
		fract->threads.worker_rend_func = fract->rend_funcs[idx + FUNC_BLOCK_S];
		fract->threads.is_multithread = 0;
		if (fract->fract_mode == E_MANDELBROT_JULIA_PREVIEW)
		{
			fract->render_func = &rend_p_mandelbrot_julia_preview;
		}
		else if (fract->fract_mode == E_BURNING_JULIA_PREVIEW)
		{
			fract->render_func = &rend_p_burning_julia_preview;
		}
	}
	render(fract);
}

void	switch_fractals(int keysym, int is_keypressed, t_fract *fract)
{
	int	idx;

	if ((keysym == XK_1 && fract->fract_mode == E_MANDELBROT)
		|| (keysym == XK_2 && fract->fract_mode == E_BURNING)
		|| ((keysym == XK_3 && fract->fract_mode == E_MANDELBROT_JULIA)
		|| (keysym == XK_3 && fract->fract_mode == E_BURNING_JULIA)))
		return ;
	if (keysym == XK_1)
		fract->fract_mode = E_MANDELBROT;
	else if (keysym == XK_2)
		fract->fract_mode = E_BURNING;
	else
	{
		if (fract->fract_mode == E_MANDELBROT
			|| fract->fract_mode == E_MANDELBROT_JULIA_PREVIEW)
			fract->fract_mode = E_MANDELBROT_JULIA;
		else
			fract->fract_mode = E_BURNING_JULIA;
	}
	if (is_keypressed)
	{
		fract->sftx = 0.0;
		fract->sfty = 0.0;
		fract->zoom = 1.0;
		if (fract->fract_mode == E_MANDELBROT)
			fract->sftx = -0.5;
	}
	idx = (fract->fract_mode * NUM_COLOR_MODES) + fract->clr_mode;
	fract->render_func = fract->rend_funcs[idx];
	if (fract->threads.is_multithread)
		fract->render_func = &trender_progressive;
	fract->threads.worker_rend_func = fract->rend_funcs[idx + FUNC_BLOCK_S];
	fract->progressive_rend = fract->prev_progressive_rend;
	render(fract);
}
