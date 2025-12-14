/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:42:23 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/11 16:02:35 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

typedef struct s_render
{
	int		s_val[4];
	int		cur_block_x;
	int		cur_block_y;
	int		frame_count;
	int		block_s;
	int		max_frames;
	int		progressive_on;
	int		cur_s_idx;
	int		pass_pix_idx;
	int		pass_pix_total;
	int		blocks_per_frame;
	int		blocks_pf_inc;
	int		pass_stride;
	int		cur_y;
	int		pix_total;
	int		comp_blocks;
	int		total_blocks;
	float	ren_time;
}	t_render;

#endif /* RENDER_H */