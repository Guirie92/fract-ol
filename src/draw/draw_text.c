/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 10:10:20 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/14 13:11:23 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dark_panel_inlines.h"
#include "libft.h"
#include "text.h"

static inline void	draw_iter_info(t_fract *fract)
{
	int			iter;

	iter = fract->steps;
	ft_itoa_buffer(iter, &fract->text.iterations[12]);
	mlx_string_put(fract->mlx, fract->mlx_win, fract->pad.iter_x,
		fract->pad.iter_y, TEXT_CLR, fract->text.iterations);
}

static inline void	draw_perc_info(t_fract *fract, int *percentage)
{
	int	i;

	*percentage = fract->ren.comp_blocks * 100 / fract->ren.total_blocks;
	ft_itoa_buffer(*percentage, fract->text.percentage);
	i = 0;
	while (fract->text.percentage[i++])
	{
		if (!fract->text.percentage[i])
		{
			fract->text.percentage[i++] = '%';
			fract->text.percentage[i] = '\0';
		}
	}
	mlx_string_put(fract->mlx, fract->mlx_win, fract->pad.perc_x,
		fract->pad.perc_y, TEXT_CLR, fract->text.percentage);
}

static inline void	draw_rendtime_info(t_fract *fract, int percentage)
{
	int	i;

	if (percentage == 100)
	{
		ft_memmove(fract->text.render_time, INFO_RENDER, 13);
		ft_ftoa_buffer(fract->ren.ren_time,
			&fract->text.render_time[FIX_S_INFO_RENDER], 2);
		i = 0;
		while (fract->text.render_time[i++])
		{
			if (!fract->text.render_time[i])
			{
				fract->text.render_time[i++] = 's';
				fract->text.render_time[i] = '\0';
			}
		}
	}
	else
		ft_memmove(fract->text.render_time, INFO_WORKING, 11);
	mlx_string_put(fract->mlx, fract->mlx_win, fract->pad.rend_x,
		fract->pad.rend_y, TEXT_CLR, fract->text.render_time);
	draw_iter_info(fract);
}

static inline void	draw_treads_info(t_fract *fract)
{
	if (fract->threads.is_multithread == 0)
		ft_itoa_buffer(1, &fract->text.thread_count[FIX_S_INFO_THREADS]);
	else
		ft_itoa_buffer(fract->threads.num_active_threads,
			&fract->text.thread_count[15]);
	mlx_string_put(fract->mlx, fract->mlx_win, fract->pad.thrd_x,
		fract->pad.thrd_y, TEXT_CLR, fract->text.thread_count);
}

void	draw_render_info(t_fract *fract)
{
	int			percentage;
	// t_darkpanel	dp;

	// dp.start_x = fract->pad.panel_r_x;
	// dp.start_y = fract->pad.panel_r_y;
	// dp.width = fract->pad.panel_r_width;
	// dp.height = fract->pad.panel_r_height;
	// dp.op = 0.4;
	// darken_square(fract, &dp);
	// dp.start_x = fract->pad.panel_l_x;
	// dp.start_y = fract->pad.panel_l_y;
	// dp.width = fract->pad.panel_l_width;
	// dp.height = fract->pad.panel_l_height;
	// darken_square(fract, &dp);

	draw_perc_info(fract, &percentage);
	draw_rendtime_info(fract, percentage);
	draw_treads_info (fract);
	draw_julia_coords(fract);
}
