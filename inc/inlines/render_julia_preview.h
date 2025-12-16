/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_julia_preview.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:42:23 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/16 16:05:45 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_JULIA_PREVIEW_H
# define RENDER_JULIA_PREVIEW_H

# include "fractol.h"
# include "math_utils.h"

static inline void	fill_blocks_julia_preview(int py, int px, int s, t_fract *fract)
{
	int	i;
	int	k;
	int	offset;

	i = py;
	while (i < py + s && i < PANEL_JS_HEIGHT)
	{
		k = px;
		while (k < px + s && k < PANEL_JS_WIDTH)
		{
			offset = (i * fract->jimg.line_len) + (k * fract->jimg.bpp / 8);
			*(unsigned int *)(fract->jimg.addr + offset) = fract->clr;
			k++;
		}
		i++;
	}
}

static inline t_rcode	pass_check_julia_preview(t_fract *fract, int *tiles_x)
{
	int	tiles_y;

	if (fract->ren.pass_pix_idx >= fract->ren.pass_pix_total)
	{
		fract->ren.cur_s_idx++;
		if (fract->ren.cur_s_idx
			>= (int)(sizeof(fract->ren.s_val) / sizeof(int)))
		{
			fract->ren.progressive_on = 0;
			return (EBREAK);
		}
		else
		{
			fract->ren.block_s = fract->ren.s_val[fract->ren.cur_s_idx];
			*tiles_x = (PANEL_JS_WIDTH + fract->ren.block_s - 1)
				/ fract->ren.block_s;
			tiles_y = (PANEL_JS_HEIGHT + fract->ren.block_s - 1)
				/ fract->ren.block_s;
			fract->ren.pass_pix_total = *tiles_x * tiles_y;
			fract->ren.pass_pix_idx = 0;
			return (ECONTINUE);
		}
	}
	return (ENONE);
}

static inline int	compute_pix_mandelbrot_julia_preview(
	int x, int y, t_fract *fract)
{
	t_complex	z;
	t_complex	c;
	int			i;

	z.x = (x * fract->jscl.sfw + fract->jscl.offsetw);
	z.y = (y * fract->jscl.sfh + fract->jscl.offseth);
	c.x = fract->julia_r;
	c.y = fract->julia_i;
	i = 0;
	while (i < fract->steps)
	{
		z = add_comp(sq_comp(z), c);
		fract->magnitude_sq = z.x * z.x + z.y * z.y;
		if (fract->magnitude_sq > fract->esc_val)
			break ;
		i++;
	}
	return (i);
}

static inline int	compute_pix_burning_julia_preview(
	int x, int y, t_fract *fract)
{
	t_complex	z;
	t_complex	c;
	int			i;

	z.x = (x * fract->jscl.sfw + fract->jscl.offsetw);
	z.y = (y * fract->jscl.sfh + fract->jscl.offseth);
	c.x = fract->julia_r;
	c.y = fract->julia_i;
	i = 0;
	while (i < fract->steps)
	{
		z.x = fabs(z.x);
		z.y = -fabs(z.y);
		z = add_comp(sq_comp(z), c);
		fract->magnitude_sq = z.x * z.x + z.y * z.y;
		if (fract->magnitude_sq > fract->esc_val)
			break ;
		i++;
	}
	return (i);
}

#endif /* RENDER_JULIA_PREVIEW_H */