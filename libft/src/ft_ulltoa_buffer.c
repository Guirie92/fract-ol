/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:31:36 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/15 16:33:54 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ulltochr(char *s, unsigned long long n)
{
	if (n > 9)
		ulltochr(s - 1, n / 10);
	*s = (n % 10) + '0';
}

static unsigned long long	count_digits(unsigned long long n, size_t *count)
{
	unsigned long long	num;

	num = n;
	while (n > 9)
	{
		n /= 10;
		(*count)++;
	}
	return (num);
}

void	ft_ulltoa_buffer(unsigned long long n, char *buf)
{
	size_t	count;

	count = 1;
	n = count_digits(n, &count);
	ulltochr(&buf[count - 1], n);
	buf[count] = '\0';
}