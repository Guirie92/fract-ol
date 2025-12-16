/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_progressive.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:13:04 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/17 00:33:54 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* RENDER MANDELBROT */

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

/* RENDER BURNING */

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

/* RENDER MANDELBROT-JULIA */

#define RENDER_PROGRESSIVE render_progressive_mandelbrot_julia
#define RENDER_LOOP render_loop__mandelbrotjulia
#define RENDER_BLOCK render_block_mandelbrot_julia
#define COMPUTE_PIX compute_pix_mandelbrot_julia
#define PALETTE get_clr_palette
#include "render_template.h"
#undef RENDER_PROGRESSIVE
#undef RENDER_LOOP
#undef RENDER_BLOCK
#undef COMPUTE_PIX
#undef PALETTE

#define RENDER_PROGRESSIVE render_progressive_mandelbrot_julia_depth
#define RENDER_LOOP render_loop_julia_mandelbrot_depth
#define RENDER_BLOCK render_block_julia_mandelbrot_depth
#define COMPUTE_PIX compute_pix_mandelbrot_julia
#define PALETTE get_clr_palette_depth
#include "render_template.h"
#undef RENDER_PROGRESSIVE
#undef RENDER_LOOP
#undef RENDER_BLOCK
#undef COMPUTE_PIX
#undef PALETTE

/* RENDER BURNING-JULIA */

#define RENDER_PROGRESSIVE render_progressive_burning_julia
#define RENDER_LOOP render_loop_burning_julia
#define RENDER_BLOCK render_block_burning_julia
#define COMPUTE_PIX compute_pix_burning_julia
#define PALETTE get_clr_palette
#include "render_template.h"
#undef RENDER_PROGRESSIVE
#undef RENDER_LOOP
#undef RENDER_BLOCK
#undef COMPUTE_PIX
#undef PALETTE

#define RENDER_PROGRESSIVE render_progressive_burning_julia_depth
#define RENDER_LOOP render_loop_burning_julia_depth
#define RENDER_BLOCK render_block_burning_julia_depth
#define COMPUTE_PIX compute_pix_burning_julia
#define PALETTE get_clr_palette_depth
#include "render_template.h"
#undef RENDER_PROGRESSIVE
#undef RENDER_LOOP
#undef RENDER_BLOCK
#undef COMPUTE_PIX
#undef PALETTE

/* JULIA PREVIEWS */

#define REND_JULIA_PREVIEW rend_p_mandelbrot_julia_preview
#define RENDER_LOOP_JULIA_PREVIEW render_loop_mandelbrot_julia_preview
#define RENDER_BLOCK_JULIA_PREVIEW render_block_mandelbrot_julia_preview
#define COMPUTE_PIX compute_pix_mandelbrot_julia_preview
#define PALETTE get_clr_palette_depth_preview
#include "render_julia_preview_template.h"
#undef REND_JULIA_PREVIEW
#undef RENDER_LOOP_JULIA_PREVIEW
#undef RENDER_BLOCK_JULIA_PREVIEW
#undef COMPUTE_PIX
#undef PALETTE

#define REND_JULIA_PREVIEW rend_p_burning_julia_preview
#define RENDER_LOOP_JULIA_PREVIEW render_loop_burning_julia_preview
#define RENDER_BLOCK_JULIA_PREVIEW render_block_burning_julia_preview
#define COMPUTE_PIX compute_pix_burning_julia_preview
#define PALETTE get_clr_palette_depth_preview
#include "render_julia_preview_template.h"
#undef REND_JULIA_PREVIEW
#undef RENDER_LOOP_JULIA_PREVIEW
#undef RENDER_BLOCK_JULIA_PREVIEW
#undef COMPUTE_PIX
#undef PALETTE
