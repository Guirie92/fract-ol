/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_common.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:42:23 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/16 16:25:20 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_COMMON_H
# define RENDER_COMMON_H

# include "fractol.h"
# include "math_utils.h"

static inline void	fill_blocks(int py, int px, int s, t_fract *fract)
{
	int	i;
	int	k;
	int	offset;

	i = py;
	while (i < py + s && i < fract->win_height)
	{
		k = px;
		while (k < px + s && k < fract->win_width)
		{
			offset = (i * fract->img.line_len) + (k * fract->img.bpp / 8);
			*(unsigned int *)(fract->img.addr + offset) = fract->clr;
			k++;
		}
		i++;
	}
}

static inline int	pass_check(t_fract *fract, int *tiles_x)
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
			*tiles_x = (fract->win_width + fract->ren.block_s - 1)
				/ fract->ren.block_s;
			tiles_y = (fract->win_height + fract->ren.block_s - 1)
				/ fract->ren.block_s;
			fract->ren.pass_pix_total = *tiles_x * tiles_y;
			fract->ren.pass_pix_idx = 0;
			return (ECONTINUE);
		}
	}
	return (ENONE);
}

static inline int	compute_pix_mandelbrot(int x, int y, t_fract *fract)
{
	t_complex	z;
	t_complex	c;
	int			i;

	z.x = 0.0;
	z.y = 0.0;
	c.x = (x * fract->scl.sfw + fract->scl.offsetw) * fract->zoom + fract->sftx;
	c.y = (y * fract->scl.sfh + fract->scl.offseth) * fract->zoom + fract->sfty;
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

static inline int	compute_pix_burning_ship(int x, int y, t_fract *fract)
{
	t_complex	z;
	t_complex	c;
	int			i;

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
		fract->magnitude_sq = z.x * z.x + z.y * z.y;
		if (fract->magnitude_sq > fract->esc_val)
			break ;
		i++;
	}
	return (i);
}

static inline int	compute_pix_mandelbrot_julia(int x, int y, t_fract *fract)
{
	t_complex	z;
	t_complex	c;
	int			i;

	z.x = (x * fract->scl.sfw + fract->scl.offsetw) * fract->zoom + fract->sftx;
	z.y = (y * fract->scl.sfh + fract->scl.offseth) * fract->zoom + fract->sfty;
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

static inline int	compute_pix_burning_julia(int x, int y, t_fract *fract)
{
	t_complex	z;
	t_complex	c;
	int			i;

	z.x = (x * fract->scl.sfw + fract->scl.offsetw) * fract->zoom + fract->sftx;
	z.y = (y * fract->scl.sfh + fract->scl.offseth) * fract->zoom + fract->sfty;
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

/*
 * NOTES ON "CHECK ESCAPE" (fract->magnitude_sq > fract->esc_val): 
 *
 * Determines if the complex number z
 * has escaped the Mandelbrot/Julia set boundary.
 *
 * The Mandelbrot set theorem states that if the magnitude (modulus) of the 
 * complex number z, represented as |z| (hypotenuse),
 * ever exceeds 2 during iteration, 
 * the sequence is guaranteed to diverge (escape to infinity).
 * 
 * -----------------------------------------------------------------------------
 * 
 * O: THE CORRECT CHECK (Magnitude vs. Circle):
 * 
 *  - 1. Magnitude Calculation: |z| = sqrt(z.x² + z.y²)
 *  - 2. Escape Condition: |z| > 2
 * 
 * To avoid the computationally expensive square root (sqrt) function, 
 * we instead check the squared magnitude against
 * the squared escape radius (4):
 * 
 *  - z.x² + z.y² = |z|²
 * 
 *  - sq of our circle: 2² = 4
 * 
 *  - |z|² > 4
 *  - This check tests if the point lies outside the circle of radius 2.
 * 
 * (the above comes from the pythagoras theorem, where 4 (c) is the hypotenuse):
 *  - a² + b² = c² 
 * 
 * -----------------------------------------------------------------------------
 * 
 * O: WHY SQUARING?
 * 
 * if we simply compare |z| > 2 (without squaring, easy enough), then we
 * would have to sqrt |z| in order for it to be equated with the hypotenuse (c):
 * 
 *  - sqrt((z.x)² + (z.y)²) > 2
 * 	
 * 	and that's really expensive (CPU intense).
 * 
 * 
 * -----------------------------------------------------------------------------
 * 
 * X: WHY NOT USE A SQUARE CHECK (e.g., |x| > 2 OR |y| > 2)
 * 
 * A square check is incorrect because points in the corners of the square 
 * (e.g., z = 2 + 2i) are inside the square region but outside the 
 * critical escape circle.
 * 
 * Example: For z = 1.5 + 1.5i:
 * 
 *  - Square Check: |1.5| <= 2 (Passes) -> Falsely says bounded.
 *  - Magnitude Check: 1.5² + 1.5² = 4.5. Since 4.5 > 4, the point has escaped.
 */

#endif /* RENDER_COMMON_H */