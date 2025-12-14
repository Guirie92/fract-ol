/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:13:04 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/14 10:11:06 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fractol.h"
#include <stdatomic.h>

void	progressive_reset(t_fract *fract)
{
	int	tiles_x;
	int	tiles_y;

	fract->ren.cur_block_x = 0;
	fract->ren.cur_block_y = 0;
	fract->ren.frame_count = 0;
	fract->ren.cur_s_idx = 0;
	fract->ren.block_s = fract->ren.s_val[fract->ren.cur_s_idx];
	fract->ren.max_frames = fract->ren.block_s * fract->ren.block_s;
	fract->ren.progressive_on = 1;
	fract->ren.cur_s_idx = 0;
	fract->ren.block_s = fract->ren.s_val[0];
	fract->ren.progressive_on = 1;
	fract->ren.pass_pix_idx = 0;
	tiles_x = (fract->win_width + fract->ren.block_s - 1) / fract->ren.block_s;
	tiles_y = (fract->win_height + fract->ren.block_s - 1) / fract->ren.block_s;
	fract->ren.pass_pix_total = tiles_x * tiles_y;
	fract->ren.cur_y = 0;
	fract->ren.comp_blocks = 0;
	fract->ren.ren_time = 0.0;
	fract->info_panel_on = 0;
}

int	progressive_tick(void *param)
{
	t_fract	*fract;

	fract = (t_fract *)param;
	if (!fract->ren.progressive_on)
		return (0);
	fract->render_func(fract);
	return (0);
}

void	render(t_fract *fract)
{
	progressive_reset(fract);
}

static void	initialize_progressive_rend_config(t_fract *fract)
{
	int				tiles_x;
	int				tiles_y;
	int				i;
	int				s;

	fract->ren.block_s = 8;
	fract->ren.s_val[0] = 8;
	fract->ren.s_val[1] = 4;
	fract->ren.s_val[2] = 2;
	fract->ren.s_val[3] = 1;
	fract->time.timekeeper_running = 0;
	tiles_x = (fract->win_width + fract->ren.block_s - 1) / fract->ren.block_s;
	tiles_y = (fract->win_height + fract->ren.block_s - 1) / fract->ren.block_s;
	fract->ren.pix_total = tiles_x * tiles_y;
	i = 0;
	while (i < 4)
	{
		s = fract->ren.s_val[i++];
		tiles_x = (fract->win_width + s - 1) / s;
		tiles_y = (fract->win_height + s - 1) / s;
		fract->ren.total_blocks += (unsigned long)tiles_x
			* (unsigned long)tiles_y;
	}
}

int	render_init(t_fract *fract)
{
	int	thread_res;

	initialize_progressive_rend_config(fract);
	ft_memmove(fract->text.iterations, "Iterations: ", 13);
	fract->time.timekeeper_running = 1;
	thread_res = pthread_create(&fract->time.timekeeper_thread, NULL,
			elapsedtime_worker, fract);
	if (thread_res != 0)
		return (E_MEM_ERROR);
	return (ESUCESS);
}
