/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tworker_elapsedtime.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:11:21 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/13 18:28:55 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <time.h>
#include <stdatomic.h>

static inline void	check_time_budget(t_fract *fract, long long current_ns,
						long long *local_start_ns);

void	*elapsedtime_worker(void *arg)
{
	t_fract			*fract;
	struct timespec	current_time;
	long long		current_ns;
	long long		local_start_ns;
	struct timespec	ts;

	ts.tv_sec = 0;
	ts.tv_nsec = 500 * NS_PER_MICROSEC;
	fract = (t_fract *)arg;
	clock_gettime(CLOCK_MONOTONIC, &current_time);
	local_start_ns = (long long)current_time.tv_sec
		* NS_PER_SEC + current_time.tv_nsec;
	while (atomic_load(&fract->time.timekeeper_running))
	{
		clock_gettime(CLOCK_MONOTONIC, &current_time);
		current_ns = (long long)current_time.tv_sec
			* NS_PER_SEC + current_time.tv_nsec;
		check_time_budget(fract, current_ns, &local_start_ns);
		clock_nanosleep(CLOCK_MONOTONIC, 0, &ts, NULL);
	}
	return (NULL);
}

static inline void	check_time_budget(t_fract *fract, long long current_ns,
	long long *local_start_ns)
{
	const long long	elapsed = current_ns - *local_start_ns;

	if (atomic_load(&fract->time.timeout_flag) == 0)
	{
		if (elapsed > TIME_BUDGET)
			if (fract->progressive_rend)
				atomic_store(&fract->time.timeout_flag, 1);
	}
	else
		*local_start_ns = current_ns;
}
