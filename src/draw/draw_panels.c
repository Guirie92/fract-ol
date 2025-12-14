/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_panels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 20:49:27 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/14 14:21:16 by guillsan         ###   ########.fr       */
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
	// revert_darken_square_buffer(fract->dp.dp_bc, fract, &dp);
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
	dp.start_x = PADDING_PANEL_TL_X;
	dp.start_y = PADDING_PANEL_TL_Y;
	dp.width = PANEL_TL_WIDTH;
	dp.height = PANEL_TL_HEIGHT;
	dp.op = 0;
	darken_square_buffer(fract->dp.dp_bc, fract, &dp);
	// revert_darken_square_buffer(fract->dp.dp_bc, fract, &dp);
}

void	draw_julia_coords(t_fract *fract)
{
	t_darkpanel	dp;

	dp.start_x = PADDING_PANEL_TL_X;
	dp.start_y = PADDING_PANEL_TL_Y;
	dp.width = PANEL_TL_WIDTH;
	dp.height = PANEL_TL_HEIGHT;
	dp.op = 0;
	// darken_square_buffer(fract->dp.dp_bc, fract, &dp);
	darken_square(fract, &dp);
	
	ft_ftoa_buffer(fract->julia_r,
		&fract->text.julia_r[FIX_S_INFO_JULIA_RE], 9);
	ft_ftoa_buffer(fract->julia_i,
		&fract->text.julia_i[FIX_S_INFO_JULIA_IM], 9);
	mlx_string_put(fract->mlx, fract->mlx_win, PADDING_JULIA_RE_L_X,
		PADDING_JULIA_RE_L_Y, TEXT_CLR, fract->text.julia_r);
	mlx_string_put(fract->mlx, fract->mlx_win, PADDING_JULIA_IM_L_X,
		PADDING_JULIA_IM_L_Y, TEXT_CLR, fract->text.julia_i);
}
