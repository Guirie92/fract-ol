/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 23:59:52 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/13 00:14:43 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_UTILS_H
# define COLOR_UTILS_H

/* Extract components (8 bits per channel) */
static inline int	get_r(int color)
{
	return ((color >> 16) & 0xFF);
}

static inline int	get_g(int color)
{
	return ((color >> 8) & 0xFF);
}

static inline int	get_b(int color)
{
	return ((color >> 0) & 0xFF);
}

/* 
 * Re-encode a new color (keeping the alpha component the same)
 */
static inline int	create_rgba(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

static inline int	scale_channel(int c, double factor)
{
	int	val;

	val = (int)((double)c * factor);
	if (val < 0)
		return (0);
	if (val > 255)
		return (255);
	return (val);
}

#endif /* COLOR_UTILS_H */