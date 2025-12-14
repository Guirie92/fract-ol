/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atodbl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:38:22 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/01 15:50:15 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

double	ft_atodbl(const char *s)
{
	long long	integer;
	double		fractional;
	int			sign;

	if (!s)
		return (0.0);
	integer = 0;
	fractional = 0.0;
	sign = 1;
	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	if (*s == '+' || *s == '-')
		if (*s++ == '-')
			sign = -sign;
	while (*s >= '0' && *s <= '9')
		integer = integer * 10 + (*s++ - '0');
	fractional = compute_fractional(&s);
	return (((double)integer + fractional) * sign);
}
