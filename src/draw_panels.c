/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_panels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 20:49:27 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/14 10:18:08 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
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
	dp.start_x = 300;
	dp.start_y = 400;
	dp.width = 200;
	dp.height = 200;
	revert_darken_square_buffer(fract->dp.dp_bc, fract, &dp);
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
	dp.start_x = 300;
	dp.start_y = 400;
	dp.width = 200;
	dp.height = 200;
	dp.op = 0.4;
	darken_square_buffer(fract->dp.dp_bc, fract, &dp);
	// revert_darken_square_buffer(fract->dp.dp_bc, fract, &dp);
}
