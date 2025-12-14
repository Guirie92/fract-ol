/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_invalid_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 21:59:20 by guillsan          #+#    #+#             */
/*   Updated: 2025/11/29 21:58:56 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	handle_width(t_pf_data *data);
static void	print_width(ssize_t width, t_pf_data *data);
static void	handle_precision(t_pf_data *data);
static void	print_precision(ssize_t precision, t_pf_data *data);

/*
 * INVALID FORMAT:
 * 
 * (1) Flags computed first, then FMW (width), then precision, then 
 *     conversion.
 * 
 * (2) Flags are printed without repetition, and in a specific order.
 * 
 * (3) Flags that override others do not appear together, 
 *     just show the ones that have precedence ('-' over '0', or
 *     '+' over ' ', or even a negative integer over '+', though
 *     that only affects valid formats).
 * 
 * (4) width appears with its width value, or as empty '' if not present.
 * 
 * (5) precision doesn't appear if not present, and appends a 0 if no
 *     precision is specified but we had a '.' symbol, 
 *     or its value if specified.
 * 
 * (6) the order of printing is: Flags then FMW then Precision then 
 *     the format "literally", ignoring the specifier.
 *
 *
 * - SYNTAX ORDER:
 *
 *       % [flags] [width] .0  [rest of invalid string]
 *
 *
 * - FLAG ORDER ('>' indicates precedence (substitution), the greater the
 *   more precendence it has):
 * 
 *       '#'   [ '+' > ' ' ] [ '-' > '0' ]
 */
void	ft_process_invalid_format(char spcfr, t_pf_data *data)
{
	if (spcfr == '%')
		return ;
	ft_write_buffer(data, '%');
	if (data->flags.hash)
		ft_write_buffer(data, '#');
	if (data->flags.plus)
		ft_write_buffer(data, '+');
	else if (data->flags.space)
		ft_write_buffer(data, ' ');
	if (data->flags.minus)
		ft_write_buffer(data, '-');
	else if (data->flags.zero)
		ft_write_buffer(data, '0');
	handle_width(data);
	handle_precision(data);
}

static void	handle_width(t_pf_data *data)
{
	if (data->flags.width < 0)
		return ;
	print_width(data->flags.width, data);
}

static void	print_width(ssize_t width, t_pf_data *data)
{
	char	c;

	if (width > 9)
		print_width(width / 10, data);
	c = width % 10 + '0';
	ft_write_buffer(data, c);
}

static void	handle_precision(t_pf_data *data)
{
	if (data->flags.precision < 0)
		return ;
	if (data->flags.precision == 0)
	{
		ft_write_buffer(data, '.');
		ft_write_buffer(data, '0');
		return ;
	}
	ft_write_buffer(data, '.');
	print_precision(data->flags.precision, data);
}

static void	print_precision(ssize_t precision, t_pf_data *data)
{
	char	c;

	if (precision > 9)
		print_width(precision / 10, data);
	c = precision % 10 + '0';
	ft_write_buffer(data, c);
}
