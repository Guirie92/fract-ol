/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_inlines.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:42:23 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/16 23:26:28 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_INLINES_H
# define COLOR_INLINES_H

# include "fractol.h"
# include <math.h>

# define COLOR_PERIOD 100.0

static inline unsigned int	palette(double t, double shift)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	double			ts;

	ts = t + shift;
	ts = fmod(ts, 1.0);
	if (ts < 0.0)
		ts += 1.0;
	r = (unsigned char)(9 * (1 - ts) * ts * ts * ts * 255);
	g = (unsigned char)(15 * (1 - ts) * (1 - ts) * ts * ts * 255);
	b = (unsigned char)(8.5 * (1 - ts) * (1 - ts) * (1 - ts) * ts * 255);
	return ((r << 16) | (g << 8) | b);
}

static inline unsigned int	get_clr_palette_depth(double i, t_fract *fract)
{
	if (i >= fract->steps)
		return (0);
	return (palette(i / fract->steps, fract->clr_shift));
}

static inline unsigned int	get_clr_palette_depth_preview(double i, t_fract *fract)
{
	if (i >= STEPS)
		return (0);
	return (palette(i / STEPS, fract->clr_shift));
}

// static inline unsigned int	get_clr_palette_depth_preview(
// 	double i, t_fract *fract)
// {
// 	if (i >= STEPS)
// 		return (0);
// 	return (palette(i / STEPS, fract->clr_shift));
// }
// static inline unsigned int	get_clr_palette_depth_preview(
// 	double i, t_fract *fract)
// {
// 	if (i >= fract->steps)
// 		return (0);
// 	return (palette(i / STEPS, fract->clr_shift));
// }

static inline unsigned int	get_clr_palette_depth_smooth(double i,
	t_fract *fract, double mg_sq)
{
	const double	log_modulus = 0.5 * log(mg_sq);
	const double	i_smooth = (double)i + 1.0 - (log(log_modulus) * LOG2);

	if (i >= fract->steps)
		return (0);
	return (palette(i_smooth / fract->steps, fract->clr_shift));
}

static inline unsigned int	get_clr_palette(int iter, t_fract *fract)
{
	double	log_modulus;
	double	nu;
	double	t;

	log_modulus = 0.5 * log(fract->magnitude_sq);
	nu = (double)iter + 1.0 - (log(log_modulus) * LOG2);
	if (iter >= fract->steps)
		return (0);
	t = fmod(nu, COLOR_PERIOD);
	if (t < 0.0)
		t += COLOR_PERIOD;
	t /= COLOR_PERIOD;
	return (palette(t, fract->clr_shift));
}

static inline unsigned int	get_clr_palette_threads(int iter,
	int steps, double nu, double shift)
{
	double	t;

	if (iter >= steps)
		return (0);
	t = fmod(nu, COLOR_PERIOD);
	if (t < 0.0)
		t += COLOR_PERIOD;
	t /= COLOR_PERIOD;
	return (palette(t, shift));
}

#endif /* COLOR_INLINES_H */