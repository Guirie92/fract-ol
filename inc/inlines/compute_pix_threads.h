/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_pix_threads.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:42:23 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/12 20:55:40 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTE_PIX_THREADS_H
# define COMPUTE_PIX_THREADS_H

# include "fractol.h"
# include "color_inlines.h"

static inline unsigned int	compute_color(int i, double magnitude_sq,
	t_fract *fract)
{
	const double	log_modulus = 0.5 * log(magnitude_sq);
	const double	nu = (double)i + 1.0 - (log(log_modulus) * LOG2);
	unsigned int	color;

	if (i == fract->steps)
		color = 0;
	else
		color = get_clr_palette_threads(i, fract->steps, nu, fract->clr_shift);
	return (color);
}

static inline unsigned int	compute_color_depth(int i, double magnitude_sq,
	t_fract *fract)
{
	(void)magnitude_sq;
	return (get_clr_palette_depth(i, fract));
}

#endif /* COMPUTE_PIX_THREADS_H */