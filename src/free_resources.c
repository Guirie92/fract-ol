/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:13:04 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/15 12:06:45 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdatomic.h>

void	free_res(t_fract *fract, int exit_status)
{
	atomic_store(&fract->time.timekeeper_running, 0);
	pthread_join(fract->time.timekeeper_thread, NULL);
	thread_destroy_pool(fract);
	if (fract->mlx && fract->img.img)
		mlx_destroy_image(fract->mlx, fract->img.img);
	if (fract->mlx && fract->panel.img)
		mlx_destroy_image(fract->mlx, fract->panel.img);
	if (fract->mlx && fract->mlx_win)
		mlx_destroy_window(fract->mlx, fract->mlx_win);
	if (fract->mlx)
		mlx_destroy_display(fract->mlx);
	free(fract->mlx);
	if (fract->dp.dp_bl)
		free(fract->dp.dp_bl);
	if (fract->dp.dp_br)
		free(fract->dp.dp_br);
	if (fract->dp.dp_bc)
		free(fract->dp.dp_bc);
	exit (exit_status);
}
