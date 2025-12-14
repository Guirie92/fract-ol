/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tworker_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:13:04 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/13 04:12:55 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <unistd.h> // For sysconf on Linux/macOS
#ifdef __APPLE__
# include <sys/sysctl.h> // For sysctl on macOS/BSD
#elif defined _WIN32
# include <windows.h> // For GetSystemInfo on Windows
#endif

#ifdef _WIN32

int	get_thread_count(void)
{
	SYSTEM_INFO	sysinfo;

	GetSystemInfo(&sysinfo);
	return ((int)sysinfo.dwNumberOfProcessors);
}

#elif defined(__APPLE__) || defined(__linux__) || defined(__unix__)
/* Standard POSIX way on most modern systems */

int	get_thread_count(void)
{
	const long	nprocs = sysconf(_SC_NPROCESSORS_ONLN);

	if (nprocs > 0)
		return ((int)nprocs);
	return (4);
}

#else

int	get_thread_count(void)
{
	return (4);
}
#endif

void	thread_init_pool(t_fract *fract)
{
	int	i;

	fract->threads.num_active_threads = get_thread_count();
	fract->threads.pool_running = 1;
	fract->threads.work_ready = 0;
	if (fract->threads.worker_rend_func == NULL)
		fract->threads.worker_rend_func = &worker_rend_mandelbrot;
	pthread_mutex_init(&fract->threads.pool_mutex, NULL);
	pthread_cond_init(&fract->threads.cond_start_work, NULL);
	pthread_cond_init(&fract->threads.cond_frame_done, NULL);
	pthread_mutex_init(&fract->threads.ren_index_mutex, NULL);
	pthread_mutex_init(&fract->threads.ren_transition_mutex, NULL);
	i = 0;
	while (i < fract->threads.num_active_threads)
		pthread_create(&fract->threads.pool_threads[i++], NULL,
			render_worker, fract);
}

void	thread_destroy_pool(t_fract *fract)
{
	int	i;

	pthread_mutex_lock(&fract->threads.pool_mutex);
	fract->threads.pool_running = 0;
	fract->threads.work_ready = 1;
	pthread_cond_broadcast(&fract->threads.cond_start_work);
	pthread_mutex_unlock(&fract->threads.pool_mutex);
	i = 0;
	while (i < fract->threads.num_active_threads)
		pthread_join(fract->threads.pool_threads[i++], NULL);
	pthread_mutex_destroy(&fract->threads.pool_mutex);
	pthread_cond_destroy(&fract->threads.cond_start_work);
	pthread_cond_destroy(&fract->threads.cond_frame_done);
	pthread_mutex_destroy(&fract->threads.ren_index_mutex);
	pthread_mutex_destroy(&fract->threads.ren_transition_mutex);
}
