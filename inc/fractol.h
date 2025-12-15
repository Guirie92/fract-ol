/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 21:44:25 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/15 18:37:43 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

/* define of the posix for CLOCK_MONOTONIC */
# ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 200112L
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include "mlx.h"
# include "error.h"
# include "data.h"
# include "defines.h"
# include "text.h"
# include "events.h"
# include "render.h"
# include "threads_render.h"

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef void			(*t_render_func)(t_fract *);

typedef struct s_fract
{
	t_text			text;
	t_render		ren;
	t_img			img;
	t_img			panel;
	t_img			jimg;
	t_scale			scl;
	t_fract_mode	fract_mode;
	t_frametime		time;
	t_rcode			rcode;
	t_panel_pad		pad;
	t_screenres		screenres;
	t_threads		threads;
	t_color_mode	clr_mode;
	t_dpanels		dp;
	char			*help_lines[HELPL_SIZE];
	void			*rend_funcs[12];
	t_render_func	render_func;
	void			*mlx;
	void			*mlx_win;
	char			*name;
	double			esc_val;
	double			sftx;
	double			sfty;
	double			zoom;
	double			julia_r;
	double			julia_i;
	double			magnitude_sq;
	double			clr_shift;
	int				steps;
	float			inv_max;
	float			factor;
	int				clr_esc;
	int				clr_bnd;
	int				clr_mandset;
	int				clr_offset;
	int				is_panning;
	int				last_x;
	int				last_y;
	unsigned int	clr;
	int				win_width;
	int				win_height;
	int				info_panel_on;
	int				progressive_rend;
}	t_fract;

int		init(t_fract *fract);
void	events_init(t_fract *fract);
void	render(t_fract *fract);
void	free_res(t_fract *fract, int exit_status);
int		parse_args(t_fract *fract, char **av);
void	compute_padding(t_fract *fract);
void	ft_log(int fd, char *msg);
void	exit_message(int fd, char *msg);

int		progressive_tick(void *param);
void	progressive_reset(t_fract *fract);

void	trender_progressive(t_fract *fract);

void	render_progressive_mandelbrot(t_fract *fract);
void	render_progressive_mandelbrot_depth(t_fract *fract);
void	render_progressive_burning(t_fract *fract);
void	render_progressive_burning_depth(t_fract *fract);
void	render_progressive_julia(t_fract *fract);
void	render_progressive_julia_depth(t_fract *fract);

void	worker_rend_mandelbrot(t_worker_data *data, t_fract *fract);
void	worker_rend_mandelbrot_depth(t_worker_data *data, t_fract *fract);
void	worker_rend_julia(t_worker_data *data, t_fract *fract);
void	worker_rend_julia_depth(t_worker_data *data, t_fract *fract);
void	worker_rend_burning(t_worker_data *data, t_fract *fract);
void	worker_rend_burning_depth(t_worker_data *data, t_fract *fract);

void	compute_pix_to_fract_scale(t_fract *fract);
int		init_panels(t_fract *fract);
int		render_init(t_fract *fract);
void	*elapsedtime_worker(void *arg);
void	draw_render_info(t_fract *fract);
void	draw_help_panel(t_fract *fract);
void	switch_fractals(int keysym, t_fract *fract);
void	revert_dp(t_fract *fract);
void	draw_dp(t_fract *fract);
void	init_text(t_fract *fract);
void	draw_julia_coords(t_fract *fract);

#endif /* FRACTOL_H */