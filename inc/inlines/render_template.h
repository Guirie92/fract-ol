/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_template.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:42:23 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/14 13:11:20 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color_inlines.h"
#include "render_common.h"

#include "libft.h"
#include "timing.h"
#include <stdatomic.h>
#include <math.h>

static inline void	RENDER_BLOCK(int bx, int by, t_fract *fract)
{
	int	s;
	int	px0;
	int	py0;
	int	px_center;
	int	py_center;

	s = fract->ren.block_s;
	px0 = bx * s;
	py0 = by * s;
	px_center = px0 + s / 2;
	py_center = py0 + s / 2;
	if (px_center >= fract->win_width)
		px_center = fract->win_width - 1;
	if (py_center >= fract->win_height)
		py_center = fract->win_height - 1;
	fract->clr = PALETTE(COMPUTE_PIX(px_center, py_center, fract), fract);
	fill_blocks(py0, px0, s, fract);
}

static inline void	RENDER_LOOP(t_fract *fract, int *tiles_x)
{
	int	rendered;
	int	shuf_idx;
	int	bx;
	int	by;

	rendered = 0;
	while (rendered < fract->ren.total_blocks)
	{
		fract->rcode = pass_check(fract, tiles_x);
		if (fract->rcode == EBREAK)
			break ;
		else if (fract->rcode == ECONTINUE)
			continue ;
		shuf_idx = shufidx(fract->ren.pass_pix_idx, fract->ren.pass_pix_total);
		bx = shuf_idx % *tiles_x;
		by = shuf_idx / *tiles_x;
		RENDER_BLOCK(bx, by, fract);
		fract->ren.pass_pix_idx++;
		fract->ren.comp_blocks++;
		rendered++;
		if (atomic_load(&fract->time.timeout_flag) == 1)
			break ;
	}
}

// void	RENDER_PROGRESSIVE(t_fract *fract)
// {
// 	int			tiles_x;
// 	t_timing	t;

// 	timing_start(&t);
// 	atomic_store(&fract->time.timeout_flag, 0);
// 	if (!fract->ren.progressive_on)
// 		return ;
// 	tiles_x = (fract->win_width + fract->ren.block_s - 1) / fract->ren.block_s;
// 	RENDER_LOOP(fract, &tiles_x);
// 	mlx_put_image_to_window(fract->mlx, fract->mlx_win, fract->img.img, 0, 0);
// 	fract->ren.ren_time += timing_read_current_s(&t);
// 	draw_render_info(fract);
// }




void	RENDER_PROGRESSIVE(t_fract *fract)
{
	int			tiles_x;
	t_timing	t;

	timing_start(&t);
	atomic_store(&fract->time.timeout_flag, 0);
	if (!fract->ren.progressive_on)
		return ;
	revert_dp(fract);
	tiles_x = (fract->win_width + fract->ren.block_s - 1) / fract->ren.block_s;
	RENDER_LOOP(fract, &tiles_x);

	draw_dp(fract);
	mlx_put_image_to_window(fract->mlx, fract->mlx_win, fract->img.img, 0, 0);
	fract->ren.ren_time += timing_read_current_s(&t);
	draw_render_info(fract);
}
