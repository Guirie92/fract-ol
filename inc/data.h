/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:42:23 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/15 12:09:43 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

typedef enum e_rcode
{
	EERROR,
	E_MEM_ERROR,
	E_SUCCESS,
	EBREAK,
	ECONTINUE,
	ENONE
}	t_rcode;

typedef enum e_fract_mode
{
	E_MANDELBROT,
	E_JULIA,
	E_BURNING,
}	t_fract_mode;

typedef enum e_color_type
{
	E_CLR_GRADIENT,
	E_CLR_MODE
}	t_color_type;

typedef enum e_color_mode
{
	E_CLR_DEFAULT,
	E_CLR_DEEP
}	t_color_mode;

typedef enum e_screenres
{
	E_DEFAULT,
	E_2K,
	E_4K,
}	t_screenres;

typedef struct s_panel_pad
{
	int	thrd_x;
	int	thrd_y;
	int	iter_x;
	int	iter_y;
	int	rend_x;
	int	rend_y;
	int	perc_x;
	int	perc_y;
	int	panel_l_x;
	int	panel_l_y;
	int	panel_r_x;
	int	panel_r_y;
	int	panel_l_width;
	int	panel_l_height;
	int	panel_r_width;
	int	panel_r_height;
}	t_panel_pad;

typedef struct s_text
{
	char	percentage[5];
	char	iterations[17];
	char	render_time[32];
	char	thread_count[32];
	char	julia_r[32];
	char	julia_i[32];
}	t_text;

typedef struct s_data
{
	t_fract_mode	fract_mode;
	double			julia_r;
	double			julia_i;
}	t_data;

typedef struct s_dpanels
{
	int	*dp_bl;
	int	*dp_br;
	int	*dp_bc;
}	t_dpanels;

typedef struct s_frametime
{
	_Atomic long long	current_elapsed_ns;
	_Atomic long long	time_start_ns;
	_Atomic int			timekeeper_running;
	_Atomic int			timeout_flag;
	pthread_t			timekeeper_thread;
}	t_frametime;

typedef struct s_scale
{
	double	sfw;
	double	sfh;
	int		offsetw;
	int		offseth;
}	t_scale;

#endif /* DATA_H */