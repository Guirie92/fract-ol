/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_template_julia_preview.h                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:42:23 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/16 15:50:53 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color_inlines.h"
#include "render_common.h"
#include "render_julia_preview.h"

#include "libft.h"
#include "timing.h"
#include <stdatomic.h>
#include <math.h>


static inline void	RENDER_BLOCK_JULIA_PREVIEW(int bx, int by, t_fract *fract)
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
	if (px_center >= PANEL_JS_WIDTH)
		px_center = PANEL_JS_WIDTH - 1;
	if (py_center >= PANEL_JS_HEIGHT)
		py_center = PANEL_JS_HEIGHT - 1;
	fract->clr = PALETTE(COMPUTE_PIX(px_center, py_center, fract), fract);
	fill_blocks_julia_preview(py0, px0, s, fract);
}

static inline void	RENDER_LOOP_JULIA_PREVIEW(t_fract *fract, int *tiles_x)
{
	int	rendered;
	int	shuf_idx;
	int	bx;
	int	by;

	rendered = 0;
	while (rendered < fract->ren.total_blocks)
	{
		fract->rcode = pass_check_julia_preview(fract, tiles_x);
		if (fract->rcode == EBREAK)
			break ;
		else if (fract->rcode == ECONTINUE)
			continue ;
		shuf_idx = shufidx(fract->ren.pass_pix_idx, fract->ren.pass_pix_total);
		bx = shuf_idx % *tiles_x;
		by = shuf_idx / *tiles_x;
		RENDER_BLOCK_JULIA_PREVIEW(bx, by, fract);
		fract->ren.pass_pix_idx++;
		fract->ren.comp_blocks++;
		rendered++;
		if (atomic_load(&fract->time.timeout_flag) == 1)
			break ;
	}
}

void	RENDER_PROGRESSIVE_JULIA_PREVIEW(t_fract *fract)
{
	int			tiles_x;
	t_timing	t;

	timing_start(&t);
	atomic_store(&fract->time.timeout_flag, 0);
	if (!fract->ren.progressive_on)
		return ;
	revert_dp(fract);
	tiles_x = (PANEL_JS_WIDTH + fract->ren.block_s - 1) / fract->ren.block_s;
	RENDER_LOOP_JULIA_PREVIEW(fract, &tiles_x);

	draw_dp(fract);
	mlx_put_image_to_window(fract->mlx, fract->mlx_win, fract->jimg.img,
		fract->win_width - PADDING_PANEL_JS_X,
		fract->win_height - PADDING_PANEL_JS_Y);
	fract->ren.ren_time += timing_read_current_s(&t);
	draw_render_info(fract);
}
