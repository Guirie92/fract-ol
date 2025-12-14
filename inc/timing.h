/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:18:59 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/13 03:00:15 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMING_H
# define TIMING_H

# include <time.h>
# include <stdint.h>

typedef struct s_timing
{
	struct timespec	start;
	struct timespec	end;
	int64_t			elapsed_ns;
}	t_timing;

static inline void	timing_start(t_timing *t)
{
	clock_gettime(CLOCK_MONOTONIC, &t->start);
}

static inline void	timing_stop(t_timing *t)
{
	clock_gettime(CLOCK_MONOTONIC, &t->end);
}

static inline int64_t	timing_read_current_ns(const t_timing *t)
{
	unsigned long long	sec_diff;
	unsigned long long	nsec_diff;
	struct timespec		current;

	clock_gettime(CLOCK_MONOTONIC, &current);
	sec_diff = (int64_t)(current.tv_sec - t->start.tv_sec);
	nsec_diff = (int64_t)(current.tv_nsec - t->start.tv_nsec);
	return (sec_diff * 1000000000LL + nsec_diff);
}

static inline int64_t	timing_read_current_ms(const t_timing *t)
{
	return (timing_read_current_ns(t) / 1000000LL);
}

static inline float	timing_read_current_s(const t_timing *t)
{
	return ((float)timing_read_current_ns(t) / 1e9f);
}

#endif // TIMING_H