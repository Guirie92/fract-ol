/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:34:19 by guillsan          #+#    #+#             */
/*   Updated: 2025/11/29 21:58:56 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	itochr(char *s, int n)
{
	if (n > 9)
		itochr(s - 1, n / 10);
	*s = (n % 10) + '0';
}

static void	count_digits(int n, size_t *dgts)
{
	if (n == 0)
		(*dgts)++;
	while (n > 0)
	{
		n /= 10;
		(*dgts)++;
	}
}

static void	process_negative(int *n, char **buf, size_t *dgts, t_pf_data *data)
{
	if (*n < 0)
	{
		if (!data->has_flag)
		{
			**buf = '-';
			(*dgts)++;
		}
		(*n) *= -1;
	}
}

int	ft_itoa_print(int n, char *buf, t_pf_data *data)
{
	size_t		dgts;
	const char	*int_min;

	if (!buf)
		return (0);
	dgts = 0;
	int_min = INT_MIN_STR;
	if (n == INT_MIN)
	{
		if (!data->has_flag)
			buf[dgts++] = '-';
		while (*int_min)
			buf[dgts++] = *int_min++;
		buf[dgts] = '\0';
		return (dgts);
	}
	process_negative(&n, &buf, &dgts, data);
	count_digits(n, &dgts);
	itochr(&buf[dgts - 1], n);
	buf[dgts] = '\0';
	return (dgts);
}
