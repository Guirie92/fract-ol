/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trender_progressive.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:13:04 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/16 23:58:36 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* TRENDER MANDELBROT */
#define WORKER_RENDER worker_rend_mandelbrot
#define RENDER_BLOCK render_block_mandelbrot_threads
#define COMPUTE_PIX compute_pix_mandelbrot_threads
#define PALETTE compute_color
#include "render_threads_template.h"
#undef WORKER_RENDER
#undef RENDER_BLOCK
#undef COMPUTE_PIX
#undef PALETTE

#define WORKER_RENDER worker_rend_mandelbrot_depth
#define RENDER_BLOCK render_block_mandelbrot_threads_depth
#define COMPUTE_PIX compute_pix_mandelbrot_threads
#define PALETTE compute_color_depth
#include "render_threads_template.h"
#undef WORKER_RENDER
#undef RENDER_BLOCK
#undef COMPUTE_PIX
#undef PALETTE

/* TRENDER BURNING */

#define WORKER_RENDER worker_rend_burning
#define RENDER_BLOCK render_block_burning_threads
#define COMPUTE_PIX compute_pix_burning_ship_threads
#define PALETTE compute_color
#include "render_threads_template.h"
#undef WORKER_RENDER
#undef RENDER_BLOCK
#undef COMPUTE_PIX
#undef PALETTE

#define WORKER_RENDER worker_rend_burning_depth
#define RENDER_BLOCK render_block_burning_threads_depth
#define COMPUTE_PIX compute_pix_burning_ship_threads
#define PALETTE compute_color_depth
#include "render_threads_template.h"
#undef WORKER_RENDER
#undef RENDER_BLOCK
#undef COMPUTE_PIX
#undef PALETTE

/* TRENDER MANDELBROT-JULIA */

#define WORKER_RENDER worker_rend_mandelbrot_julia
#define RENDER_BLOCK render_block_mandelbrot_julia_threads
#define COMPUTE_PIX compute_pix_julia_threads
#define PALETTE compute_color
#include "render_threads_template.h"
#undef WORKER_RENDER
#undef RENDER_BLOCK
#undef COMPUTE_PIX
#undef PALETTE

#define WORKER_RENDER worker_rend_mandelbrot_julia_depth
#define RENDER_BLOCK render_block_mandelbrot_julia_threads_depth
#define COMPUTE_PIX compute_pix_julia_threads
#define PALETTE compute_color_depth
#include "render_threads_template.h"
#undef WORKER_RENDER
#undef RENDER_BLOCK
#undef COMPUTE_PIX
#undef PALETTE

/* TRENDER BURNING-JULIA */

#define WORKER_RENDER worker_rend_burning_julia
#define RENDER_BLOCK render_block_burning_julia_threads
#define COMPUTE_PIX compute_pix_julia_threads
#define PALETTE compute_color
#include "render_threads_template.h"
#undef WORKER_RENDER
#undef RENDER_BLOCK
#undef COMPUTE_PIX
#undef PALETTE

#define WORKER_RENDER worker_rend_burning_julia_depth
#define RENDER_BLOCK render_block_burning_julia_threads_depth
#define COMPUTE_PIX compute_pix_julia_threads
#define PALETTE compute_color_depth
#include "render_threads_template.h"
#undef WORKER_RENDER
#undef RENDER_BLOCK
#undef COMPUTE_PIX
#undef PALETTE


/* JULIA PREVIEWS */

#define WORKER_RENDER_JULIA_PREVIEW worker_mandelbrot_julia_preview
#define RENDER_BLOCK_JULIA_PREVIEW render_block_mandelbrot_julia_preview_threads
#define COMPUTE_PIX compute_pix_mandelbrot_julia_preview_threads
#define PALETTE compute_color_julia_preview
#include "render_julia_preview_threads_template.h"
#undef WORKER_RENDER_JULIA_PREVIEW
#undef RENDER_BLOCK_JULIA_PREVIEW
#undef COMPUTE_PIX
#undef PALETTE

#define WORKER_RENDER_JULIA_PREVIEW worker_burning_julia_preview
#define RENDER_BLOCK_JULIA_PREVIEW render_loop_burning_julia_preview_threads
#define COMPUTE_PIX compute_pix_burning_julia_preview_threads
#define PALETTE compute_color_depth_julia_preview
#include "render_julia_preview_threads_template.h"
#undef WORKER_RENDER_JULIA_PREVIEW
#undef RENDER_BLOCK_JULIA_PREVIEW
#undef COMPUTE_PIX
#undef PALETTE


void	*render_worker(void *arg)
{
	t_fract			*fract;
	t_worker_data	data;

	fract = (t_fract *)arg;
	while (1)
	{
		pthread_mutex_lock(&fract->threads.pool_mutex);
		while (!fract->threads.work_ready && fract->threads.pool_running)
			pthread_cond_wait(&fract->threads.cond_start_work,
				&fract->threads.pool_mutex);
		if (!fract->threads.pool_running)
		{
			pthread_mutex_unlock(&fract->threads.pool_mutex);
			break ;
		}
		pthread_mutex_unlock(&fract->threads.pool_mutex);
		fract->threads.worker_rend_func(&data, fract);
		pthread_mutex_lock(&fract->threads.pool_mutex);
		fract->threads.threads_done_cnt++;
		if (fract->threads.threads_done_cnt
			== fract->threads.num_active_threads)
			pthread_cond_signal(&fract->threads.cond_frame_done);
		pthread_mutex_unlock(&fract->threads.pool_mutex);
	}
	return (NULL);
}

void	trender_progressive(t_fract *fract)
{
	t_timing	t;

	timing_start(&t);
	if (!fract->ren.progressive_on)
		return ;
	if (fract->ren.pass_pix_idx == 0 && fract->ren.cur_s_idx == 0)
		atomic_store(&fract->ren.comp_blocks, 0);
	atomic_store(&fract->time.timeout_flag, 0);
	revert_dp(fract);
	pthread_mutex_lock(&fract->threads.pool_mutex);
	fract->threads.threads_done_cnt = 0;
	fract->threads.work_ready = 1;
	pthread_cond_broadcast(&fract->threads.cond_start_work);
	while (fract->threads.threads_done_cnt < fract->threads.num_active_threads)
		pthread_cond_wait(&fract->threads.cond_frame_done,
			&fract->threads.pool_mutex);
	fract->threads.work_ready = 0;
	pthread_mutex_unlock(&fract->threads.pool_mutex);
	draw_dp(fract);
	mlx_put_image_to_window(fract->mlx, fract->mlx_win, fract->img.img, 0, 0);
	fract->ren.ren_time += timing_read_current_s(&t);
	draw_render_info(fract);
}

void	trender_progressive_julia_prev(t_fract *fract)
{
	t_timing	t;

	timing_start(&t);
	if (!fract->ren.progressive_on)
		return ;
	if (fract->ren.pass_pix_idx == 0 && fract->ren.cur_s_idx == 0)
		atomic_store(&fract->ren.comp_blocks, 0);
	atomic_store(&fract->time.timeout_flag, 0);
	revert_dp(fract);
	pthread_mutex_lock(&fract->threads.pool_mutex);
	fract->threads.threads_done_cnt = 0;
	fract->threads.work_ready = 1;
	pthread_cond_broadcast(&fract->threads.cond_start_work);
	while (fract->threads.threads_done_cnt < fract->threads.num_active_threads)
		pthread_cond_wait(&fract->threads.cond_frame_done,
			&fract->threads.pool_mutex);
	fract->threads.work_ready = 0;
	pthread_mutex_unlock(&fract->threads.pool_mutex);
	draw_dp(fract);
		mlx_put_image_to_window(fract->mlx, fract->mlx_win, fract->jimg.img,
		fract->win_width - fract->j_preview_width,
		fract->win_height - fract->j_preview_height);
	fract->ren.ren_time += timing_read_current_s(&t);
	draw_render_info(fract);
}
