/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_render.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:42:23 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/16 23:34:23 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_RENDER_H
# define THREADS_RENDER_H

# define MAX_THREADS 200
# include <pthread.h>

/* b -> block
 * p -> pixel
 * s -> size
 * b -> block
 */
typedef struct s_worker_data
{
	int	shuf_idx;
	int	bx;
	int	by;
	int	tx;
	int	pass_idx;
	int	block_s;
	int	pass_total;
}	t_worker_data;

typedef struct s_fract	t_fract;
typedef void			(*t_worker_rend_func) (t_worker_data *, t_fract *);

typedef struct s_threads
{
	t_worker_rend_func	worker_rend_func;
	t_worker_rend_func	prev_worker_rend_func;

	/* Thread Pool Control */
	pthread_t			pool_threads[MAX_THREADS];
	int					num_active_threads;

	/* The "Master Lock" for pool synchronization */
	pthread_mutex_t		pool_mutex;

	/* Signals */
	/* main commands threads to go */
	pthread_cond_t		cond_start_work;
	/* threads tell main they're done with their work */
	pthread_cond_t		cond_frame_done;

	/* State Flags */
	/* 1 = keep threads alive, 0 = kill threads (exit app) */
	int					pool_running;
	/* 1 = there is work to do */
	int					work_ready;
	/* counter: how many threads finished the current frame */
	int					threads_done_cnt;

	pthread_mutex_t		ren_index_mutex;
	pthread_mutex_t		ren_transition_mutex;

	int					is_multithread;
}	t_threads;

void	*render_worker(void *arg);
void	thread_init_pool(t_fract *fract);
void	thread_destroy_pool(t_fract *fract);

#endif /* THREADS_RENDER_H */