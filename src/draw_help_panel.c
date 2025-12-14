/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_help_panel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:11:21 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/13 20:50:33 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "text.h"
#include "dark_panel_inlines.h"
#include "libft.h"

static void	init_dark_panels(t_fract *fract)
{
	unsigned int	size;

	size = fract->pad.panel_l_width * fract->pad.panel_l_height;
	fract->dp.dp_bl = malloc(size * sizeof(int));
	size = fract->pad.panel_r_width * fract->pad.panel_r_height;
	fract->dp.dp_br = malloc(size * sizeof(int));
	size = 200 * 200;
	fract->dp.dp_bc = malloc(size * sizeof(int));
}

void	init_panels(t_fract *fract)
{
	const char *const	tmp[HELPL_SIZE] = {
		HELP_L1, HELP_L2, HELP_L3, HELP_L4, HELP_L5, HELP_L6, HELP_L7, HELP_L8,
		HELP_L9, HELP_L10, HELP_L11, HELP_L12, HELP_L13, HELP_L14, HELP_L15,
		HELP_L16, HELP_L17, HELP_L18, HELP_L19, HELP_L20, HELP_L21, HELP_L22,
		HELP_L23, HELP_L24, HELP_L25, HELP_L26, HELP_L27, HELP_L28, HELP_L29,
		HELP_L30, HELP_L31, HELP_L32, HELP_L33, HELP_L34, HELP_L35
	};

	ft_memmove(fract->help_lines, tmp, sizeof(tmp));
	init_dark_panels(fract);
}

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
