/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:42:23 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/15 19:37:20 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define EXEC_NAME       "fractol"
# define MANDELBROT_NAME "mandelbrot"
# define BURNING_NAME    "burning"
# define JULIA_NAME      "julia"

# define JULIA_DEFAULT_R_VAL -0.8
# define JULIA_DEFAULT_I_VAL 0.156

# define MANDELBROT_NAME_LEN 10
# define BURNING_NAME_LEN    7
# define JULIA_NAME_LEN      5

# define MANDELBROT_RANGE_MIN -3
# define MANDELBROT_RANGE_MAX  3

/* colors */
# define BLACK         0x000000
# define WHITE         0xFFFFFF
# define RED           0xFF0000
# define GREEN         0x00FF00
# define BLUE          0x0000FF
# define DARK_BLUE     0x07077D
# define YELLOW        0xFFFF00
# define BRIGHT_YELLOW 0xFCFC00
# define CYAN          0x00FFFF
# define MAGENTA       0xFF00FF
# define ORANGE        0xFFA500
# define DARK_PURPLE   0x010002
# define PURPLE        0x800080
# define VIOLET        0x7600EC
# define GRAY          0x808080
# define LIGHT_GRAY    0xC0C0C0
# define DARK_GRAY     0x404040
# define BROWN         0xA52A2A
# define PINK          0xFFC0CB
# define GOLD          0xFFD700
# define SILVER        0xC0C0C0
# define PALETTE_SIZE  21

/* console colors */
# define CLR_RED "\033[31m"
# define CLR_GLD "\033[38;2;255;215;0m"
# define CLR_RST "\033[0m"

# define NS_PER_SEC    1000000000LL
# define NS_PER_MICROSEC 1000

/* LOG2 = (1.0 / log(2.0)) */
# define LOG2 1.4426950408889634

# define WIDTH  1000
# define HEIGHT 900

# define WIDTH_2K  1700
# define HEIGHT_2K 1700

# define WIDTH_4K  3820
# define HEIGHT_4K 2120

# define STEPS 150
# define STEPS_MIN  0
# define STEPS_MAX  5000
# define STEPS_INC  10

# define BLOCKS_PF_MIN   8192
# define BLOCKS_PF_MAX   58000

# define BLOCKS_PF_STEP_CAP 1500

# define SHIFT_AMOUNT 0.5

# define ZOOM_AMOUNT 0.18

# define PRIME_STRIDE 1299827

# define NUM_FRACTALS 3 
# define NUM_COLOR_MODES 2

/* FUNC_BLOCK_S = (NUM_FRACTALS * NUM_COLOR_MODES) */
# define FUNC_BLOCK_S 6

# define PADDING_PANEL_JS_X 350
# define PADDING_PANEL_JS_Y 350
# define PANEL_JS_WIDTH 350
# define PANEL_JS_HEIGHT 350

# define PADDING_THREAD_L_X_MUL 0.045
# define PADDING_THREAD_L_Y_MUL 0.936

# define PADDING_ITER_L_X_MUL 0.045
# define PADDING_ITER_L_Y_MUL 0.952

# define PADDING_REND_L_X_MUL 0.045
# define PADDING_REND_L_Y_MUL 0.975

# define PADDING_PERC_R_X_MUL 0.935
# define PADDING_PERC_R_Y_MUL 0.975

# define PADDING_PANEL_L_X_MUL 0.035
# define PADDING_PANEL_L_Y_MUL 0.919

# define PADDING_PANEL_R_X_MUL 0.929
# define PADDING_PANEL_R_Y_MUL 0.961

# define PANEL_L_WIDTH_MUL 0.125
# define PANEL_L_HEIGHT_MUL 0.064

# define PANEL_R_WIDTH_MUL 0.035
# define PANEL_R_HEIGHT_MUL 0.018

# define PADDING_JULIA_RE_L_X 15
# define PADDING_JULIA_RE_L_Y 25
# define PADDING_JULIA_IM_L_X 15
# define PADDING_JULIA_IM_L_Y 40

# define PADDING_PANEL_TL_X 10
# define PADDING_PANEL_TL_Y 10
# define PANEL_TL_WIDTH 118
# define PANEL_TL_HEIGHT 35

# define PADDING_THREAD_L_X 25
# define PADDING_THREAD_L_Y 58

# define PADDING_ITER_L_X 25
# define PADDING_ITER_L_Y 43

# define PADDING_REND_L_X 25
# define PADDING_REND_L_Y 23

# define PADDING_PERC_R_X 45
# define PADDING_PERC_R_Y 23

# define PADDING_PANEL_L_X 15
# define PADDING_PANEL_L_Y 73

# define PADDING_PANEL_R_X 51
# define PADDING_PANEL_R_Y 35

# define PANEL_L_WIDTH 125
# define PANEL_L_HEIGHT 58

# define PANEL_R_WIDTH 35
# define PANEL_R_HEIGHT 16

/* 10 MS -> 10 * 1,000,000 nanoseconds (16 MS = 60fps) */
# define TIME_BUDGET 10000000LL

#endif /* DEFINES_H */