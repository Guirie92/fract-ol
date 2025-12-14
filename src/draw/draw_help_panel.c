/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_help_panel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:11:21 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/14 12:44:33 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "text.h"
#include "dark_panel_inlines.h"
#include "libft.h"

void	draw_help_panel(t_fract *fract)
{
	int			text_x;
	int			y_pos;
	int			i;
	t_darkpanel	dp;

	dp.start_x = (fract->win_width - INFO_PANEL_WIDTH) / 2;
	dp.start_y = (fract->win_height - INFO_PANEL_HEIGHT) / 2;
	dp.width = INFO_PANEL_WIDTH;
	dp.height = INFO_PANEL_HEIGHT;
	dp.op = 0.15;
	text_x = dp.start_x + TXT_PADDING_X;
	y_pos = dp.start_y + ((INFO_PANEL_WIDTH - (13 * LINE_H)) / 2)
		- TXT_PADDING_Y;
	fract->ren.progressive_on = 0;
	darken_square(fract, &dp);
	i = 0;
	while (i < HELPL_SIZE)
	{
		mlx_string_put(fract->mlx, fract->mlx_win, text_x,
			y_pos, TEXT_CLR, fract->help_lines[i]);
		y_pos += LINE_H;
		i++;
	}
}
