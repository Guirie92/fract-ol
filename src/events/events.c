/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:13:04 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/17 04:18:15 by guillsan         ###   ########.fr       */
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

/* It renders just the outline, 4 lines, without traversing the whole pixel
 * matrix. Loops go:
 * - top
 * - bottom
 * - left
 * - right
 */
static void render_window_outline(t_fract *fract)
{
	int	y;
	int	x;
	
	y = 0;
	while (y < OUTLINE_THICKNESS)
	{
		x = 0;
		while (x < fract->j_preview_width)
		{
			int offset = (y * fract->jimg.line_len) + (x * fract->jimg.bpp / 8);
			*(unsigned int *)(fract->jimg.addr + offset) = GRAY;
			x++;
		}
		y++;
	} 
	y = fract->j_preview_height - OUTLINE_THICKNESS;
	while (y < fract->j_preview_height)
	{
		x = 0;
	    while (x < fract->j_preview_width)
		{
	        int offset = (y * fract->jimg.line_len) + (x * fract->jimg.bpp / 8);
			*(unsigned int *)(fract->jimg.addr + offset) = GRAY;
			x++;
	    }
		y++;
	}
	y = OUTLINE_THICKNESS;
	while (y < fract->j_preview_height - OUTLINE_THICKNESS)
	{
		x = 0;
	    while (x < OUTLINE_THICKNESS) {
	        int offset = (y * fract->jimg.line_len) + (x * fract->jimg.bpp / 8);
			*(unsigned int *)(fract->jimg.addr + offset) = GRAY;
			x++;
	    }
		y++;
	}
	y = OUTLINE_THICKNESS;
	while (y < fract->j_preview_height - OUTLINE_THICKNESS)
	{
		x = fract->j_preview_width - OUTLINE_THICKNESS;
	    while (x < fract->j_preview_width)
		{
	        int offset = (y * fract->jimg.line_len) + (x * fract->jimg.bpp / 8);
			*(unsigned int *)(fract->jimg.addr + offset) = GRAY;
			x++;
	    }
		y++;
	}
}

static void toggle_julia_preview(t_fract *fract)
{
	if (fract->fract_mode == E_MANDELBROT
		|| fract->fract_mode == E_BURNING)
	{
		compute_pix_to_fract_scale_julia_preview(fract);
		render_window_outline(fract);
		fract->prev_fract_mode = fract->fract_mode;
		fract->prev_render_func = fract->render_func;
		fract->threads.prev_worker_rend_func = fract->threads.worker_rend_func;
		fract->prev_progressive_rend = fract->progressive_rend;
		fract->progressive_rend = 0;
		if (fract->fract_mode == E_MANDELBROT)
		{
			fract->fract_mode = E_MANDELBROT_JULIA_PREVIEW;
			fract->render_func = &rend_p_mandelbrot_julia_preview;
			if (fract->threads.is_multithread)
				fract->render_func = &trender_progressive_julia_preview;
			fract->threads.worker_rend_func = &worker_mandelbrot_julia_preview;
		}
		else
		{
			fract->fract_mode = E_BURNING_JULIA_PREVIEW;
			fract->render_func = &rend_p_burning_julia_preview;
			if (fract->threads.is_multithread)
				fract->render_func = &trender_progressive_julia_preview;
			fract->threads.worker_rend_func = &worker_burning_julia_preview;
		}
		draw_julia_coords(fract);
		render(fract);
	}
	else if (fract->fract_mode == E_MANDELBROT_JULIA_PREVIEW
			|| fract->fract_mode == E_BURNING_JULIA_PREVIEW)
	{
		fract->progressive_rend = fract->prev_progressive_rend;
		fract->fract_mode = fract->prev_fract_mode;

		fract->render_func = fract->prev_render_func;
		if (fract->threads.is_multithread)
			fract->render_func = &trender_progressive;
		fract->threads.worker_rend_func = fract->threads.prev_worker_rend_func;
		
		render(fract);
	}
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
		switch_fractals(keysym, 1, fract);
	else if (keysym == XK_j || keysym == XK_J)
		toggle_julia_preview(fract);
}

int	key_handler(int keysym, t_fract *fract)
{
	check_keys_movement(keysym, fract);
	check_keys_general(keysym, fract);
	return (0);
}

void	toggle_progressive_renderer(t_fract *fract)
{
	if (fract->fract_mode == E_MANDELBROT_JULIA_PREVIEW
		|| fract->fract_mode == E_BURNING_JULIA_PREVIEW)
		return ;
	if (fract->progressive_rend)
		fract->progressive_rend = 0;
	else
		fract->progressive_rend = 1;
}
