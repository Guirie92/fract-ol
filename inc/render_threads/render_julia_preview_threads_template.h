/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_julia_preview_threads_template.h            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:42:23 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/17 00:32:07 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute_pix_threads.h"
#include "color_inlines.h"
#include "render_common_j_preview_threads.h"

#include "libft.h"
#include "fractol.h"
#include "color_inlines.h"
#include "timing.h"
#include <math.h>

static inline void	RENDER_BLOCK_JULIA_PREVIEW(int bx, int by, t_fract *fract)
{
	t_trend_data	rd;
	int				iter;

	rd.s = fract->ren.block_s;
	rd.px = bx * rd.s + OUTLINE_THICKNESS;
	rd.py = by * rd.s + OUTLINE_THICKNESS;
	rd.px_center = rd.px + rd.s / 2;
	rd.py_center = rd.py + rd.s / 2;
	rd.mg_sq = 0.0;
	if (rd.px_center >= fract->j_preview_width - OUTLINE_THICKNESS)
		rd.px_center = fract->j_preview_width - OUTLINE_THICKNESS - 1;
	if (rd.py_center >= fract->j_preview_height - OUTLINE_THICKNESS)
		rd.py_center = fract->j_preview_height - OUTLINE_THICKNESS - 1;
	iter = COMPUTE_PIX(rd.px_center, rd.py_center, fract, &rd.mg_sq);
	rd.color = PALETTE(iter, rd.mg_sq, fract);
	fill_blocks_julia_preview(&rd, fract);
}

inline void	WORKER_RENDER_JULIA_PREVIEW(t_worker_data *local, t_fract *fract)
{
	while (1)
	{
		if (atomic_load(&fract->time.timeout_flag) == 1
			|| !fract->ren.progressive_on)
			break ;
		local->pass_idx = atomic_fetch_add_explicit(&fract->ren.pass_pix_idx, 1,
				memory_order_relaxed);
		local->block_s = atomic_load_explicit(&fract->ren.block_s,
				memory_order_relaxed);
		local->pass_total = atomic_load_explicit(
				&fract->ren.pass_pix_total, memory_order_relaxed);
		if (local->pass_idx >= local->pass_total)
		{
			pass_check_julia_preview(fract);
			if (!fract->ren.progressive_on)
				break ;
			continue ;
		}
		local->shuf_idx = shufidx(local->pass_idx, local->pass_total);
		local->tx = (fract->j_preview_width + local->block_s - 1) / local->block_s;
		local->bx = local->shuf_idx % local->tx;
		local->by = local->shuf_idx / local->tx;
		RENDER_BLOCK_JULIA_PREVIEW(local->bx, local->by, fract);
		atomic_fetch_add(&fract->ren.comp_blocks, 1);
	}
}
