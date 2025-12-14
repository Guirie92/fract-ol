/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:04:18 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/05 23:10:36 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	itochr(char *s, int n)
{
	if (n > 9)
		itochr(s - 1, n / 10);
	*s = (n % 10) + '0';
}

static int	count_digits(int n, int *sign, size_t *count)
{
	int	num;

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

void	ft_itoa_buffer(int n, char *buf)
{
	size_t	count;
	int		sign;
	char	*min;

	sign = 1;
	count = 1;
	if (n == INT_MIN)
	{
		min = "-2147483648";
		while (*min)
			*buf++ = *min++;
		*buf = '\0';
		return;
	}
	n = count_digits(n, &sign, &count);
	if (sign < 0)
		*buf = '-';
	itochr(&buf[count - 1], n);
	buf[count] = '\0';
}