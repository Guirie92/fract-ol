/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_evaluation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:30:31 by guillsan          #+#    #+#             */
/*   Updated: 2025/11/29 21:58:56 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_flags_handler.h"

static void	determine_sign(int spcfr, t_pf_data *data, va_list *args);
static void	determine_prefix(int spcfr, t_pf_data *data, va_list *args);
static void	determine_padding(int spcfr, t_pf_data *data, va_list *args);
static void	determine_precision_len(int spcfr, t_pf_data *data, int *arglen);

void	ft_evaluate_flags(char const **str, t_pf_data *data, va_list *args)
{
	int	spcfr;

	spcfr = **str;
	data->flags.specifier = spcfr;
	if (data->flags.precision >= 0
		&& (spcfr != 'c' && spcfr != 's'))
		data->flags.zero = 0;
	if (spcfr == 'c' || spcfr == 's')
		data->flags.zero = 0;
	if (spcfr == 'p')
		if (data->flags.precision >= 0)
			data->flags.zero = 0;
	determine_sign(spcfr, data, args);
	ft_handle_ptr_sign_id(spcfr, data, args);
	determine_prefix(spcfr, data, args);
	determine_padding(spcfr, data, args);
}

static void	determine_sign(int spcfr, t_pf_data *data, va_list *args)
{
	va_list	args_tmp;
	int		arg;

	if (spcfr != 'd' && spcfr != 'i')
		return ;
	va_copy(args_tmp, *args);
	arg = va_arg(args_tmp, int);
	if (arg < 0)
	{
		data->flags.sign = '-';
		data->flags.prefixlen++;
	}
	else if (data->flags.plus)
	{
		data->flags.sign = '+';
		data->flags.prefixlen++;
	}
	else if (data->flags.space)
	{
		data->flags.sign = ' ';
		data->flags.prefixlen++;
	}
	va_end(args_tmp);
}

static void	determine_prefix(int spcfr, t_pf_data *data, va_list *args)
{
	va_list			args_tmp;
	unsigned int	arg;

	if (!(data->flags.hash) || (spcfr != 'x' && spcfr != 'X' && spcfr != 'o'))
		return ;
	va_copy(args_tmp, *args);
	arg = va_arg(args_tmp, unsigned int);
	if (spcfr == 'x' && arg != 0)
	{
		data->flags.prefix[0] = '0';
		data->flags.prefix[1] = 'x';
		data->flags.prefixlen += 2;
	}
	else if (spcfr == 'X' && arg != 0)
	{
		data->flags.prefix[0] = '0';
		data->flags.prefix[1] = 'X';
		data->flags.prefixlen += 2;
	}
	else if (spcfr == 'o' && arg != 0)
	{
		data->flags.prefix[0] = '0';
		data->flags.prefixlen++;
	}
	va_end(args_tmp);
}

/*
 * Total width is: total - (format length + prefix + sign)
 * 
 * total_width at start holds the value for prefix + sign.
 */
static void	determine_padding(int spcfr, t_pf_data *data, va_list *args)
{
	int	arglen;

	arglen = ft_calculate_arglen(spcfr, data, args);
	if (spcfr == 'o' && arglen == 0 && data->flags.precision == 0
		&& data->flags.hash != 1)
		arglen = 0;
	if (spcfr == 's')
	{
		if (data->flags.precision >= 0 && arglen > data->flags.precision)
			arglen = data->flags.precision;
		if (arglen < 0)
			arglen = 0;
	}
	else if (spcfr == 'c')
		data->flags.precision = 0;
	else
		determine_precision_len(spcfr, data, &arglen);
	data->flags.padding = data->flags.width - (arglen + data->flags.prefixlen);
	if (spcfr == 'o')
		data->flags.padding = data->flags.width - arglen;
	if (data->flags.padding < 0)
		data->flags.padding = 0;
}

static void	determine_precision_len(int spcfr, t_pf_data *data, int *arglen)
{
	if (spcfr == 'o')
		*arglen += data->flags.prefixlen;
	if (data->flags.precision > *arglen)
	{
		data->flags.precisionlen = data->flags.precision - *arglen;
		*arglen = data->flags.precision;
	}
}
