/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dark_panel_inlines.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:42:23 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/17 04:12:32 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DARK_PANEL_INLINES_H
# define DARK_PANEL_INLINES_H

# include "fractol.h"
# include "color_utils.h"
# include "math_utils.h"

typedef struct s_darkpanel
{
	int		start_x;
	int		start_y;
	int		width;
	int		height;
	double	op;
}	t_darkpanel;

/* calculates the memory offset for (x, y)
 * and
 * reads the 4 bytes as a single unsigned integer
*/
static inline unsigned int	get_pixel_color(t_fract *fract, int x, int y)
{
	char	*pix_addr;

	pix_addr = fract->img.addr + (y * fract->img.line_len
			+ x * (fract->img.bpp / 8));
	return (*(unsigned int *)pix_addr);
}

static inline int	darken_color(int original_color, double factor)
{
	int	a;
	int	r;
	int	g;
	int	b;

	factor = clamp01(factor);
	a = (original_color >> 24) & 0xFF;
	r = scale_channel(get_r(original_color), factor);
	g = scale_channel(get_g(original_color), factor);
	b = scale_channel(get_b(original_color), factor);
	return (create_rgba(a, r, g, b));
}

static inline void	darken_square(t_fract *fract, t_darkpanel *dp)
{
	int	x;
	int	y;
	int	color;

	y = dp->start_y;
	while (y < dp->start_y + dp->height)
	{
		x = dp->start_x;
		while (x < dp->start_x + dp->width)
		{
			color = get_pixel_color(fract, x, y);
			color = darken_color(color, dp->op);
			mlx_pixel_put(fract->mlx, fract->mlx_win, x, y, color);
			x++;
		}
		y++;
	}
}


static inline void	darken_square_buffer(int *buffer,
	t_fract *fract, t_darkpanel *dp)
{
	int	x;
	int	y;
	int	color;
	int	offset;
	int	buf_idx;

	y = dp->start_y;
	buf_idx = 0;
	while (y < dp->start_y + dp->height)
	{
		x = dp->start_x;
		while (x < dp->start_x + dp->width)
		{
			color = get_pixel_color(fract, x, y);
			buffer[buf_idx++] = color;
			color = darken_color(color, dp->op);
			offset = (y * fract->img.line_len) + (x * fract->img.bpp / 8);
			*(unsigned int *)(fract->img.addr + offset) = color;
			x++;
		}
		y++;
	}
}

static inline void	darken_square_buffer_panel(int *buffer,
	t_fract *fract, t_darkpanel *dp)
{
	int	x;
	int	y;
	int	color;
	int	offset;
	int	buf_idx;

	y = dp->start_y;
	buf_idx = 0;
	while (y < dp->start_y + dp->height)
	{
		x = dp->start_x;
		while (x < dp->start_x + dp->width)
		{
			color = get_pixel_color(fract, x, y);
			buffer[buf_idx++] = color;
			color = darken_color(color, dp->op);
			offset = ((y - dp->start_y) * fract->panel.line_len) + ((x - dp->start_x) * fract->panel.bpp / 8);
			*(unsigned int *)(fract->panel.addr + offset) = color;
			x++;
		}
		y++;
	}
}

static inline void	darken_square_buffer_panel_width(int *buffer,
	t_fract *fract, t_darkpanel *dp, int width)
{
	int	x;
	int	y;
	int	color;
	int	offset;
	int	buf_idx;

	y = dp->start_y;
	buf_idx = 0;
	while (y < dp->start_y + dp->height)
	{
		x = dp->start_x;
		while (x < dp->start_x + width)
		{
			color = get_pixel_color(fract, x, y);
			buffer[buf_idx++] = color;
			if (x < dp->width)
				color = darken_color(color, dp->op);
			offset = ((y - dp->start_y) * fract->panel.line_len) + ((x - dp->start_x) * fract->panel.bpp / 8);
			*(unsigned int *)(fract->panel.addr + offset) = color;
			x++;
		}
		y++;
	}
}

static inline void	revert_darken_square_buffer(int *buffer,
	t_fract *fract, t_darkpanel *dp)
{
	int	x;
	int	y;
	int	offset;
	int	buf_idx;

	y = dp->start_y;
	buf_idx = 0;
	while (y < dp->start_y + dp->height)
	{
		x = dp->start_x;
		while (x < dp->start_x + dp->width)
		{
			offset = (y * fract->img.line_len) + (x * fract->img.bpp / 8);
			*(unsigned int *)(fract->img.addr + offset) = buffer[buf_idx++];
			x++;
		}
		y++;
	}
}

#endif /* DARK_PANEL_INLINES_H */