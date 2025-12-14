/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:42:23 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/13 01:26:19 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# include "defines.h"
# include <math.h>

typedef struct s_lerp
{
	int	new_min;
	int	new_max;
	int	old_min;
	int	old_max;
}	t_lerp;

typedef struct s_complex
{
	double	x;
	double	y;
}	t_complex;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	r1;
	unsigned char	g1;
	unsigned char	b1;
	unsigned char	r2;
	unsigned char	g2;
	unsigned char	b2;
}	t_color;

typedef struct s_fract	t_fract;

/* Formula for scaling down a range with known min and max values:
 * https://stackoverflow.com/questions/5294955/
 * how-to-scl-down-a-range-of-numbers-with-a-known-min-and-max-value 
 */
static inline double	scale_factor(t_lerp *lerp)
{
	double	res;

	res = (double)(lerp->new_max - lerp->new_min);
	res /= (double)(lerp->old_max - lerp->old_min);
	return (res);
}

static inline double	clamp01(double x)
{
	if (x < 0.0)
		return (0.0);
	if (x > 1.0)
		return (1.0);
	return (x);
}

static inline t_complex	add_comp(t_complex z1, t_complex z2)
{
	t_complex	res;

	res.x = z1.x + z2.x;
	res.y = z1.y + z2.y;
	return (res);
}

/*
 * Complex square (z²):
 *
 * For z, as a composition of z.x and z.y (x + yi),
 * we expand:
 *
 *  - (x + yi)²
 *  - =
 *  - (x + yi) * (x + yi)
 *  - =
 *  -  x² + xyi + xyi + y²i²
 *  - =
 *  -  x² + 2xyi + y²(-1)
 *  - =
 *  -  x² + 2xyi - y²
 *  - =
 *  - x² - y² + 2xyi
 *
 * Therefore:
 *   real part      = x² - y²
 *   imaginary part = 2xy
 * 
 * PS:typing the squared symbol (²):
 *   WIN:    ALT + 0178
 *   MACOS:  OPT + 00B2
 *   LINUX:  Compose → ^2
 */
static inline t_complex	sq_comp(t_complex z)
{
	t_complex	res;

	res.x = (z.x * z.x) - (z.y * z.y);
	res.y = 2 * z.x * z.y;
	return (res);
}

static inline int	shufidx(int index, int total)
{
	long long	v;

	if (total <= 1)
		return (0);
	v = (long long)index * (long long)PRIME_STRIDE;
	return ((int)(v % (long long)total));
}

#endif /* MATH_UTILS_H */