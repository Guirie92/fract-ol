/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ui64toa_base_print.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:34:19 by guillsan          #+#    #+#             */
/*   Updated: 2025/11/29 23:51:58 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ui64tochr(char *chr, unsigned long long n, int base,
				const char *base_table)
{
	size_t	idx;

	if (n / base > 0)
		ui64tochr(chr - 1, n / base, base, base_table);
	idx = n % base;
	*chr = base_table[idx];
}

static int	count_digits(unsigned long long n, int base)
{
	int	dgts;

	dgts = 0;
	while (n > 0)
	{
		n /= base;
		dgts++;
	}
	return (dgts);
}

static void	initialize_base(const char **base_table, int *base,
	t_pf_base e_base)
{
	*base = 10;
	*base_table = BASE_10;
	if (e_base == EBASE_16LC)
	{
		*base = 16;
		*base_table = BASE_16LC;
	}
	else if (e_base == EBASE_16UC)
	{
		*base = 16;
		*base_table = BASE_16UC;
	}
	else if (e_base == EBASE_8)
	{
		*base = 8;
		*base_table = BASE_8;
	}
}

int	ft_ui64toa_base_print(unsigned long long n, t_pf_base e_base, char *buffer)
{
	int			dgts;
	int			base;
	const char	*base_table;

	if (!buffer)
		return (0);
	dgts = 0;
	initialize_base(&base_table, &base, e_base);
	if (n == 0)
	{
		buffer[0] = '0';
		buffer[1] = '\0';
		return (1);
	}
	dgts = count_digits(n, base);
	ui64tochr(&buffer[dgts - 1], n, base, base_table);
	buffer[dgts] = '\0';
	return (dgts);
}
