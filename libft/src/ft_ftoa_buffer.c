/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:29:38 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/14 11:39:36 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline long long	process_integral(float nb, float *fp, char **buf,
							int decimals);
static inline void		process_fractional(float fp, long long *f, char **buf,
							int decimals);

void	ft_ftoa_buffer(float nb, char *buf, int decimals)
{
	long long	ip;
	float		fp;
	char		tmp[32];
	char		*p;
	long long	fractional;

	if (decimals > 9)
		decimals = 9;
	ip = process_integral(nb, &fp, &buf, decimals);
	ft_itoa_buffer(ip, tmp);
	p = tmp;
	while (*p)
		*buf++ = *p++;
	if (decimals > 0)
	{
		*buf++ = '.';
		process_fractional(fp, &fractional, &buf, decimals);
		ft_itoa_buffer(fractional, tmp);
		p = tmp;
		while (*p)
			*buf++ = *p++;
	}
	*buf = '\0';
}

/*
 * This is a trick I learned to round decimals: you want to add a leading
 * x.5 number to the decimal part to round it up. The number of 0s for
 * the x.5 round variable depends on the "decimals" count. So, for instance, 
 * if you have 1.999, the x.5 will be -> 0.005 (thus the 0.5f / round).
 * 
 * This outputs things like 1.999 -> 2 (since 1.999 + 0.005 = 2.004 = 2)
 */
static inline long long	process_integral(float nb, float *fp, char **buf,
	int decimals)
{
	long long	ip;
	float		round;
	int			i;

	if (nb < 0.0f)
	{
		*(*buf)++ = '-';
		nb = -nb;
	}
	round = 1.0f;
	i = 0;
	while (i++ < decimals)
		round *= 10.0f;
	nb += (0.5f / round);
	ip = (long long)nb;
	*fp = nb - (float)ip;
	return (ip);
}

/*
 * fractional part * scale + 0.5f is a standard way to implement
 * round to nearest, which is similar to the method used in printf(%f)
 */
static inline void	process_fractional(float fp, long long *f, char **buf,
	int decimals)
{
	float		scale;
	int			i;
	int			zeros;
	long long	nb_tmp;

	scale = 1.0f;
	i = 0;
	while (i++ < decimals)
		scale *= 10.0f;
	*f = (long long)(fp * scale + 0.5f);
	zeros = decimals - 1;
	nb_tmp = *f;
	while (nb_tmp >= 10)
	{
		nb_tmp /= 10;
		zeros--;
	}
	while (zeros-- > 0)
		*(*buf)++ = '0';
}
