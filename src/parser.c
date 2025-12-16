/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:13:04 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/16 16:46:34 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fractol.h"

static inline double	compute_fractional(const char **s)
{
	double	fractional;
	double	scale;

	fractional = 0.0;
	scale = 1.0;
	if (**s == '.')
		(*s)++;
	while (**s >= '0' && **s <= '9')
	{
		scale *= 10;
		fractional = fractional + (**s - '0') / scale;
		(*s)++;
	}
	return (fractional);
}

static int	validate_arg(const char *s)
{
	if (!s || !*s)
		return (EERROR);
	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	if (*s == '+' || *s == '-')
		s++;
	if (!(*s >= '0' && *s <= '9') && *s != '.')
		return (EERROR);
	while (*s >= '0' && *s <= '9')
		s++;
	if (*s == '.')
		s++;
	while (*s >= '0' && *s <= '9')
		s++;
	if (!*s)
		return (E_SUCCESS);
	else
		return (EERROR);
}

int	parse_args(t_fract *fract, char **av)
{
	if (validate_arg(av[2]) == EERROR)
		return (EERROR);
	if (validate_arg(av[3]) == EERROR)
		return (EERROR);
	fract->fract_mode = E_MANDELBROT_JULIA;
	fract->julia_r = ft_atodbl(av[2]);
	fract->julia_i = ft_atodbl(av[3]);
	return (E_SUCCESS);
}
