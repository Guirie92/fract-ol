/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:13:04 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/16 15:13:18 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "math_utils.h"
#include "fractol.h"

void	compute_padding(t_fract *fract)
{
	fract->pad.thrd_x = PADDING_THREAD_L_X;
	fract->pad.thrd_y = fract->win_height - PADDING_THREAD_L_Y;
	fract->pad.iter_x = PADDING_ITER_L_X;
	fract->pad.iter_y = fract->win_height - PADDING_ITER_L_Y;
	fract->pad.rend_x = PADDING_REND_L_X;
	fract->pad.rend_y = fract->win_height - PADDING_REND_L_Y;
	fract->pad.perc_x = fract->win_width - PADDING_PERC_R_X;
	fract->pad.perc_y = fract->win_height - PADDING_PERC_R_Y;
	fract->pad.panel_l_x = PADDING_PANEL_L_X;
	fract->pad.panel_l_y = fract->win_height - PADDING_PANEL_L_Y;
	fract->pad.panel_r_x = fract->win_width - PADDING_PANEL_R_X;
	fract->pad.panel_r_y = fract->win_height - PADDING_PANEL_R_Y;

}

void	compute_pix_to_fract_scale(t_fract *fract)
{
	int		size;
	t_lerp	lerp;

	if (fract->win_width > fract->win_height)
		size = fract->win_height;
	else
		size = fract->win_width;
	lerp.new_min = MANDELBROT_RANGE_MIN;
	lerp.new_max = MANDELBROT_RANGE_MAX;
	lerp.old_min = 0;
	lerp.old_max = size;
	fract->scl.sfw = scale_factor(&lerp);
	fract->scl.offsetw = lerp.new_min - (lerp.old_min * fract->scl.sfw);
	lerp.new_min = MANDELBROT_RANGE_MAX;
	lerp.new_max = MANDELBROT_RANGE_MIN;
	lerp.old_min = 0;
	lerp.old_max = size;
	fract->scl.sfh = scale_factor(&lerp);
	fract->scl.offseth = lerp.new_min - (lerp.old_min * fract->scl.sfh);
}

void	compute_pix_to_fract_scale_julia_preview(t_fract *fract)
{
	int		size;
	t_lerp	lerp;

	if (PANEL_JS_WIDTH > PANEL_JS_HEIGHT)
		size = PANEL_JS_HEIGHT;
	else
		size = PANEL_JS_WIDTH;
	lerp.new_min = MANDELBROT_RANGE_MIN;
	lerp.new_max = MANDELBROT_RANGE_MAX;
	lerp.old_min = 0;
	lerp.old_max = size;
	fract->jscl.sfw = scale_factor(&lerp);
	fract->jscl.offsetw = lerp.new_min - (lerp.old_min * fract->jscl.sfw);
	lerp.new_min = MANDELBROT_RANGE_MAX;
	lerp.new_max = MANDELBROT_RANGE_MIN;
	lerp.old_min = 0;
	lerp.old_max = size;
	fract->jscl.sfh = scale_factor(&lerp);
	fract->jscl.offseth = lerp.new_min - (lerp.old_min * fract->jscl.sfh);
}

static void	init_rend_funcs(t_fract *fract)
{
	fract->rend_funcs[0] = &render_progressive_mandelbrot;
	fract->rend_funcs[1] = &render_progressive_mandelbrot_depth;
	fract->rend_funcs[2] = &render_progressive_julia;
	fract->rend_funcs[3] = &render_progressive_julia_depth;
	fract->rend_funcs[4] = &render_progressive_burning;
	fract->rend_funcs[5] = &render_progressive_burning_depth;
	fract->rend_funcs[6] = &worker_rend_mandelbrot;
	fract->rend_funcs[7] = &worker_rend_mandelbrot_depth;
	fract->rend_funcs[8] = &worker_rend_julia;
	fract->rend_funcs[9] = &worker_rend_julia_depth;
	fract->rend_funcs[10] = &worker_rend_burning;
	fract->rend_funcs[11] = &worker_rend_burning_depth;

	
	fract->rend_funcs[12] = &render_progressive_julia_preview;
}

static void	init_vals(t_fract *fract)
{
	fract->esc_val = (MANDELBROT_RANGE_MAX * MANDELBROT_RANGE_MAX);
	fract->steps = STEPS;
	fract->inv_max = 1.0f / fract->steps;
	fract->sfty = 0.0;
	fract->zoom = 1.0;
	fract->is_panning = 0;
	fract->screenres = E_DEFAULT;
	fract->progressive_rend = 1;
	fract->pad.panel_l_width = PANEL_L_WIDTH;
	fract->pad.panel_l_height = PANEL_L_HEIGHT;
	fract->pad.panel_r_width = PANEL_R_WIDTH;
	fract->pad.panel_r_height = PANEL_R_HEIGHT;
}

int	init(t_fract *fract)
{
	fract->name = EXEC_NAME;
	fract->mlx = mlx_init();
	if (!fract->mlx)
		return (E_MEM_ERROR);
	fract->mlx_win = mlx_new_window(fract->mlx, WIDTH, HEIGHT, fract->name);
	if (!fract->mlx_win)
		return (E_MEM_ERROR);
	fract->img.img = mlx_new_image(fract->mlx, WIDTH, HEIGHT);
	if (!fract->img.img)
		return (E_MEM_ERROR);
	fract->img.addr = mlx_get_data_addr(fract->img.img, &fract->img.bpp,
		&fract->img.line_len, &fract->img.endian);
	fract->panel.img = mlx_new_image(fract->mlx, PANEL_TL_WIDTH, PANEL_TL_HEIGHT);
	if (!fract->panel.img)
		return (E_MEM_ERROR);
	fract->panel.addr = mlx_get_data_addr(fract->panel.img, &fract->panel.bpp,
			&fract->panel.line_len, &fract->panel.endian);
	fract->jimg.img = mlx_new_image(fract->mlx, PANEL_JS_WIDTH, PANEL_JS_HEIGHT);
	if (!fract->jimg.img)
		return (E_MEM_ERROR);
	fract->jimg.addr = mlx_get_data_addr(fract->jimg.img, &fract->jimg.bpp,
			&fract->jimg.line_len, &fract->jimg.endian);
	fract->win_width = WIDTH;
	fract->win_height = HEIGHT;
	compute_pix_to_fract_scale(fract);
	init_vals(fract);
	compute_padding(fract);
	init_rend_funcs(fract);
	// init_panels(fract);
	// init_text(fract);
	if (init_panels(fract) == E_MEM_ERROR || render_init(fract) == E_MEM_ERROR)
		return (E_MEM_ERROR);
	init_text(fract);
	return (E_SUCCESS);
}
