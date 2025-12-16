/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_common_threads.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:42:23 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/16 23:28:07 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_COMMON_THREADS_H
# define RENDER_COMMON_THREADS_H

# include "fractol.h"
# include "math_utils.h"
# include <stdatomic.h>

/* fill_blocks: now takes color explicitly (thread-local) */
static inline void	fill_blocks(t_trend_data *rd, t_fract *fract)
{
	int	i;
	int	k;
	int	offset;

	i = rd->py;
	while (i < rd->py + rd->s && i < fract->win_height)
	{
		k = rd->px;
		while (k < rd->px + rd->s && k < fract->win_width)
		{
			offset = (i * fract->img.line_len) + (k * fract->img.bpp / 8);
			*(unsigned int *)(fract->img.addr + offset) = rd->color;
			k++;
		}
		i++;
	}
}

static inline void	pass_check(t_fract *fract)
{
	int	tx;
	int	ty;

	pthread_mutex_lock(&fract->threads.ren_transition_mutex);
	if (fract->ren.pass_pix_idx <= fract->ren.pass_pix_total)
	{
		pthread_mutex_unlock(&fract->threads.ren_transition_mutex);
		return ;
	}
	fract->ren.cur_s_idx++;
	if (fract->ren.cur_s_idx >= (int)(sizeof(fract->ren.s_val) / sizeof(int)))
	{
		fract->ren.progressive_on = 0;
		atomic_store(&fract->ren.comp_blocks, fract->ren.total_blocks);
	}
	else
	{
		fract->ren.block_s = fract->ren.s_val[fract->ren.cur_s_idx];
		tx = (fract->win_width + fract->ren.block_s - 1) / fract->ren.block_s;
		ty = (fract->win_height + fract->ren.block_s - 1) / fract->ren.block_s;
		fract->ren.pass_pix_total = tx * ty;
		atomic_store(&fract->ren.comp_blocks, 0);
		fract->ren.pass_pix_idx = 0;
	}
	pthread_mutex_unlock(&fract->threads.ren_transition_mutex);
}

/* 
 * compute_pix: returns color for the center pixel,
 * does NOT touch fract->clr/factor
 */
static inline int	compute_pix_mandelbrot_threads(int x, int y, t_fract *fract,
	double *out_mg_sq)
{
	t_complex	z;
	t_complex	c;
	int			i;
	double		magnitude_sq;

	magnitude_sq = 0.0;
	z.x = 0.0;
	z.y = 0.0;
	c.x = (x * fract->scl.sfw + fract->scl.offsetw) * fract->zoom + fract->sftx;
	c.y = (y * fract->scl.sfh + fract->scl.offseth) * fract->zoom + fract->sfty;
	i = 0;
	while (i < fract->steps)
	{
		z = add_comp(sq_comp(z), c);
		magnitude_sq = z.x * z.x + z.y * z.y;
		if (magnitude_sq > fract->esc_val)
			break ;
		i++;
	}
	*out_mg_sq = magnitude_sq;
	return (i);
}

static inline int	compute_pix_julia_threads(int x, int y, t_fract *fract,
	double *out_mg_sq)
{
	t_complex	z;
	t_complex	c;
	int			i;
	double		magnitude_sq;

	magnitude_sq = 0.0;
	z.x = (x * fract->scl.sfw + fract->scl.offsetw) * fract->zoom + fract->sftx;
	z.y = (y * fract->scl.sfh + fract->scl.offseth) * fract->zoom + fract->sfty;
	c.x = fract->julia_r;
	c.y = fract->julia_i;
	i = 0;
	while (i < fract->steps)
	{
		z = add_comp(sq_comp(z), c);
		magnitude_sq = z.x * z.x + z.y * z.y;
		if (magnitude_sq > fract->esc_val)
			break ;
		i++;
	}
	*out_mg_sq = magnitude_sq;
	return (i);
}

static inline int	compute_pix_burning_ship_threads(int x, int y,
	t_fract *fract, double *out_mg_sq)
{
	t_complex	z;
	t_complex	c;
	int			i;
	double		magnitude_sq;

	magnitude_sq = 0.0;
	z.x = 0.0;
	z.y = 0.0;
	c.x = (x * fract->scl.sfw + fract->scl.offsetw) * fract->zoom + fract->sftx;
	c.y = (y * fract->scl.sfh + fract->scl.offseth) * fract->zoom + fract->sfty;
	i = 0;
	while (i < fract->steps)
	{
		z.x = fabs(z.x);
		z.y = -fabs(z.y);
		z = add_comp(sq_comp(z), c);
		magnitude_sq = z.x * z.x + z.y * z.y;
		if (magnitude_sq > fract->esc_val)
			break ;
		i++;
	}
	*out_mg_sq = magnitude_sq;
	return (i);
}

#endif /* RENDER_COMMON_THREADS_H */