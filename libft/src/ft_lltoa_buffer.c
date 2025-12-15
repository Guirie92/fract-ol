/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:31:36 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/15 16:32:33 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	lltochr(char *s, long long n)
{
	if (n > 9)
		lltochr(s - 1, n / 10);
	*s = (n % 10) + '0';
}

static long long	count_digits(long long n, int *sign, size_t *count)
{
	long long	num;

	num = n;
	if (n < 0)
	{
		(*count)++;
		*sign = -1;
		n *= -1;
	}
	num = n;
	while (n > 9)
	{
		n /= 10;
		(*count)++;
	}
	return (num);
}

void	ft_lltoa_buffer(long long n, char *buf)
{
	size_t	count;
	int		sign;
	char	*min;

	sign = 1;
	count = 1;
	if (n == LLONG_MIN)
	{
		min = "-9223372036854775808";
		while (*min)
			*buf++ = *min++;
		*buf = '\0';
		return ;
	}
	n = count_digits(n, &sign, &count);
	if (sign < 0)
		*buf = '-';
	lltochr(&buf[count - 1], n);
	buf[count] = '\0';
}