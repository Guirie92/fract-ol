/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 12:43:55 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/17 04:09:00 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"

static int	init_dark_panels(t_fract *fract)
{
	unsigned int	size;

	size = fract->pad.panel_l_width * fract->pad.panel_l_height;
	fract->dp.dp_bl = malloc(size * sizeof(int));
	if (!fract->dp.dp_bl)
		return (E_MEM_ERROR);
	size = fract->pad.panel_r_width * fract->pad.panel_r_height;
	fract->dp.dp_br = malloc(size * sizeof(int));
	if (!fract->dp.dp_br)
		return (E_MEM_ERROR);
	size = PANEL_TL_WIDTH * PANEL_TL_HEIGHT;
	fract->dp.dp_tl = malloc(size * sizeof(int));
	if (!fract->dp.dp_tl)
		return (E_MEM_ERROR);
	return (E_SUCCESS);
}

int	init_panels(t_fract *fract)
{
	const char *const	tmp[HELPL_SIZE] = {
		HELP_L1, HELP_L2, HELP_L3, HELP_L4, HELP_L5, HELP_L6, HELP_L7, HELP_L8,
		HELP_L9, HELP_L10, HELP_L11, HELP_L12, HELP_L13, HELP_L14, HELP_L15,
		HELP_L16, HELP_L17, HELP_L18, HELP_L19, HELP_L20, HELP_L21, HELP_L22,
		HELP_L23, HELP_L24, HELP_L25, HELP_L26, HELP_L27, HELP_L28, HELP_L29,
		HELP_L30, HELP_L31, HELP_L32, HELP_L33, HELP_L34, HELP_L35, HELP_L36,
		HELP_L37, HELP_L38, HELP_L39, HELP_L40, HELP_L41, HELP_L42, HELP_L43,
		HELP_L44, HELP_L45, HELP_L46, HELP_L47, HELP_L48, HELP_L49, HELP_L50,
		HELP_L51, HELP_L52
	};

	ft_memmove(fract->help_lines, tmp, sizeof(tmp));
	if (init_dark_panels(fract) == E_MEM_ERROR)
		return (E_MEM_ERROR);
	return (E_SUCCESS);
}

void	init_text(t_fract *fract)
{
	ft_memmove(fract->text.thread_count, INFO_THREADS, 16);
	ft_memmove(fract->text.julia_r, INFO_JULIA_RE, 4);
	ft_memmove(fract->text.julia_i, INFO_JULIA_IM, 4);
}
