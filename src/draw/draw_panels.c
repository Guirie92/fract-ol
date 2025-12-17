/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_panels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 20:49:27 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/17 04:15:43 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include "dark_panel_inlines.h"

void	revert_dp(t_fract *fract)
{
	t_darkpanel	dp;

	dp.start_x = fract->pad.panel_l_x;
	dp.start_y = fract->pad.panel_l_y;
	dp.width = fract->pad.panel_l_width;
	dp.height = fract->pad.panel_l_height;
	revert_darken_square_buffer(fract->dp.dp_bl, fract, &dp);
	dp.start_x = fract->pad.panel_r_x;
	dp.start_y = fract->pad.panel_r_y;
	dp.width = fract->pad.panel_r_width;
	dp.height = fract->pad.panel_r_height;
	revert_darken_square_buffer(fract->dp.dp_br, fract, &dp);
	// dp.start_x = 300;
	// dp.start_y = 400;
	// dp.width = 200;
	// dp.height = 200;
	// revert_darken_square_buffer(fract->dp.dp_tl, fract, &dp);
}

void	draw_dp(t_fract *fract)
{
	t_darkpanel	dp;

	dp.start_x = fract->pad.panel_l_x;
	dp.start_y = fract->pad.panel_l_y;
	dp.width = fract->pad.panel_l_width;
	dp.height = fract->pad.panel_l_height;
	dp.op = 0.4;
	darken_square_buffer(fract->dp.dp_bl, fract, &dp);
	dp.start_x = fract->pad.panel_r_x;
	dp.start_y = fract->pad.panel_r_y;
	dp.width = fract->pad.panel_r_width;
	dp.height = fract->pad.panel_r_height;
	dp.op = 0.4;
	darken_square_buffer(fract->dp.dp_br, fract, &dp);

	
	// dp.start_x = PADDING_PANEL_TL_X;
	// dp.start_y = PADDING_PANEL_TL_Y;
	// dp.width = PANEL_TL_WIDTH;
	// dp.height = PANEL_TL_HEIGHT;
	// dp.op = 0;
	//darken_square_buffer_p(fract->dp.dp_tl, fract, &dp);
	// revert_darken_square_buffer(fract->dp.dp_tl, fract, &dp);
}

static inline void	draw_title(t_fract *fract)
{
	// if (fract->fract_mode == E_MANDELBROT)
	// 	ft_memmove(fract->text.title, MANDELBROT_TITLE, MANDELBROT_TITLE_S);
	// else if (fract->fract_mode == E_BURNING)
	// 	ft_memmove(fract->text.title, BURNING_TITLE, BURNING_TITLE_S);
	// else if (fract->fract_mode == E_MANDELBROT_JULIA)
	// 	ft_memmove(fract->text.title, MAN_JULIA_MODE, MAN_JULIA_MODE_S);
	// else if (fract->fract_mode == E_BURNING_JULIA)
	// 	ft_memmove(fract->text.title, BUR_JULIA_MODE, BUR_JULIA_MODE_S);
	// else if (fract->fract_mode == E_MANDELBROT_JULIA_PREVIEW)
	// 	ft_memmove(fract->text.title, MAN_JULIA_PREVIEW, MAN_JULIA_PREVIEW_S);
	// else if (fract->fract_mode == E_BURNING_JULIA_PREVIEW)
	// 	ft_memmove(fract->text.title, BUR_JULIA_PREVIEW, BUR_JULIA_PREVIEW_S);
	mlx_string_put(fract->mlx, fract->mlx_win, PADDING_TITLE_X,
		PADDING_TITLE_Y, TEXT_CLR, fract->text.title);
}

static inline void	select_dp_size_init_title(t_fract *fract, t_darkpanel *dp)
{
	if (fract->fract_mode == E_MANDELBROT)
	{
		ft_memmove(fract->text.title, MANDELBROT_TITLE, MANDELBROT_TITLE_S);
		dp->width = PANEL_TL_MANDELBROT_TITLE_WIDTH;
	}
	else if (fract->fract_mode == E_BURNING)
	{
		ft_memmove(fract->text.title, BURNING_TITLE, BURNING_TITLE_S);
		dp->width = PANEL_TL_BURNING_TITLE_WIDTH;
	}
	else if (fract->fract_mode == E_MANDELBROT_JULIA)
	{
		ft_memmove(fract->text.title, MAN_JULIA_MODE, MAN_JULIA_MODE_S);
		dp->width = PANEL_TL_MAN_JULIA_MODE_WIDTH;
	}
	else if (fract->fract_mode == E_BURNING_JULIA)
	{
		ft_memmove(fract->text.title, BUR_JULIA_MODE, BUR_JULIA_MODE_S);
		dp->width = PANEL_TL_BUR_JULIA_MODE_WIDTH;
	}
	else if (fract->fract_mode == E_MANDELBROT_JULIA_PREVIEW)
	{
		ft_memmove(fract->text.title, MAN_JULIA_PREVIEW, MAN_JULIA_PREVIEW_S);
		dp->width = PANEL_TL_MAN_JULIA_PREVIEW_WIDTH;
	}
	else if (fract->fract_mode == E_BURNING_JULIA_PREVIEW)
	{
		ft_memmove(fract->text.title, BUR_JULIA_PREVIEW, BUR_JULIA_PREVIEW_S);
		dp->width = PANEL_TL_BUR_JULIA_PREVIEW_WIDTH;
	}
}

void	draw_julia_coords(t_fract *fract)
{
	t_darkpanel	dp;

	dp.start_x = PADDING_PANEL_TL_X;
	dp.start_y = PADDING_PANEL_TL_Y;
	dp.width = PANEL_TL_WIDTH;
	dp.height = PANEL_TL_HEIGHT;
	dp.op = 0.4;
	select_dp_size_init_title(fract, &dp);
	darken_square_buffer_panel_width(fract->dp.dp_tl,
		fract, &dp, PANEL_TL_WIDTH);
	mlx_put_image_to_window(fract->mlx, fract->mlx_win, fract->panel.img,
		PADDING_PANEL_TL_X, PADDING_PANEL_TL_Y);
	ft_ftoa_buffer(fract->julia_r,
		&fract->text.julia_r[FIX_S_INFO_JULIA_RE], 9);
	ft_ftoa_buffer(fract->julia_i,
		&fract->text.julia_i[FIX_S_INFO_JULIA_IM], 9);
	if ((fract->julia_r > 999.9 || fract->julia_r < -999.9)
		|| (fract->julia_i > 999.9 || fract->julia_i < -999.9))
	{
		ft_memmove(&fract->text.julia_r[FIX_S_INFO_JULIA_RE], INFO_JULIA_NA, 4);
		ft_memmove(&fract->text.julia_i[FIX_S_INFO_JULIA_IM], INFO_JULIA_NA, 4);
	}
	mlx_string_put(fract->mlx, fract->mlx_win, PADDING_JULIA_RE_L_X,
		PADDING_JULIA_RE_L_Y, TEXT_CLR, fract->text.julia_r);
	mlx_string_put(fract->mlx, fract->mlx_win, PADDING_JULIA_IM_L_X,
		PADDING_JULIA_IM_L_Y, TEXT_CLR, fract->text.julia_i);
	draw_title(fract);
}
