/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:42:23 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/18 01:28:33 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

typedef struct s_render
{
	int			s_val[4];
	_Atomic int	cur_block_x;
	_Atomic int	cur_block_y;
	_Atomic int	frame_count;
	_Atomic int	block_s;
	_Atomic int	max_frames;
	_Atomic int	progressive_on;
	_Atomic int	cur_s_idx;
	_Atomic int	pass_pix_idx;
	_Atomic int	pass_pix_total;
	_Atomic int	blocks_per_frame;
	_Atomic int	blocks_pf_inc;
	_Atomic int	pass_stride;
	_Atomic int	cur_y;
	_Atomic int	pix_total;
	_Atomic int	comp_blocks;
	_Atomic int	total_blocks;
	float		ren_time;
}	t_render;

#endif /* RENDER_H */