/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_progressive.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:13:04 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/13 03:26:02 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define RENDER_PROGRESSIVE render_progressive_mandelbrot
#define RENDER_LOOP render_loop_mandelbrot
#define RENDER_BLOCK render_block_mandelbrot
#define COMPUTE_PIX compute_pix_mandelbrot
#define PALETTE get_clr_palette
#include "render_template.h"
#undef RENDER_PROGRESSIVE
#undef RENDER_LOOP
#undef RENDER_BLOCK
#undef COMPUTE_PIX
#undef PALETTE

#define RENDER_PROGRESSIVE render_progressive_mandelbrot_depth
#define RENDER_LOOP render_loop_mandelbrot_depth
#define RENDER_BLOCK render_block_mandelbrot_depth
#define COMPUTE_PIX compute_pix_mandelbrot
#define PALETTE get_clr_palette_depth
#include "render_template.h"
#undef RENDER_PROGRESSIVE
#undef RENDER_LOOP
#undef RENDER_BLOCK
#undef COMPUTE_PIX
#undef PALETTE

#define RENDER_PROGRESSIVE render_progressive_burning
#define RENDER_LOOP render_loop_burning
#define RENDER_BLOCK render_block_burning
#define COMPUTE_PIX compute_pix_burning_ship
#define PALETTE get_clr_palette
#include "render_template.h"
#undef RENDER_PROGRESSIVE
#undef RENDER_LOOP
#undef RENDER_BLOCK
#undef COMPUTE_PIX
#undef PALETTE

#define RENDER_PROGRESSIVE render_progressive_burning_depth
#define RENDER_LOOP render_loop_burning_depth
#define RENDER_BLOCK render_block_burning_depth
#define COMPUTE_PIX compute_pix_burning_ship
#define PALETTE get_clr_palette_depth
#include "render_template.h"
#undef RENDER_PROGRESSIVE
#undef RENDER_LOOP
#undef RENDER_BLOCK
#undef COMPUTE_PIX
#undef PALETTE

#define RENDER_PROGRESSIVE render_progressive_julia
#define RENDER_LOOP render_loop_julia
#define RENDER_BLOCK render_block_julia
#define COMPUTE_PIX compute_pix_julia
#define PALETTE get_clr_palette
#include "render_template.h"
#undef RENDER_PROGRESSIVE
#undef RENDER_LOOP
#undef RENDER_BLOCK
#undef COMPUTE_PIX
#undef PALETTE

#define RENDER_PROGRESSIVE render_progressive_julia_depth
#define RENDER_LOOP render_loop_julia_depth
#define RENDER_BLOCK render_block_julia_depth
#define COMPUTE_PIX compute_pix_julia
#define PALETTE get_clr_palette_depth
#include "render_template.h"
#undef RENDER_PROGRESSIVE
#undef RENDER_LOOP
#undef RENDER_BLOCK
#undef COMPUTE_PIX
#undef PALETTE
