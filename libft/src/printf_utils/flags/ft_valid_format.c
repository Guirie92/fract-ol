/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 21:59:24 by guillsan          #+#    #+#             */
/*   Updated: 2025/11/29 21:59:12 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	process_flag_zero(int spcfr, t_pf_data *data, va_list *args,
				char padchr);
static void	process_flag_space(int spcfr, t_pf_data *data, va_list *args,
				char padchr);
static void	print_arg(int spcfr, t_pf_data *data, va_list *args);
static void	print_precision(t_pf_data *data);

void	ft_process_valid_format(const char **str, t_pf_data *data,
	va_list *args)
{
	char	padchar;

	data->is_writing_mode = TRUE;
	if (data->flags.zero)
		padchar = '0';
	else
		padchar = ' ';
	if (data->flags.minus)
	{
		print_arg(**str, data, args);
		while ((data->flags.padding)--)
			ft_write_buffer(data, padchar);
	}
	else
	{
		if (padchar == '0')
			process_flag_zero(**str, data, args, padchar);
		else
			process_flag_space(**str, data, args, padchar);
	}
	(*str)++;
}

static void	process_flag_zero(int spcfr, t_pf_data *data, va_list *args,
	char padchr)
{
	if (data->flags.sign)
		ft_write_buffer(data, data->flags.sign);
	if (data->flags.prefix[0])
		ft_write_buffer(data, data->flags.prefix[0]);
	if (data->flags.prefix[1])
		ft_write_buffer(data, data->flags.prefix[1]);
	if (data->flags.is_ptr_nil)
		while ((data->flags.padding)--)
			ft_write_buffer(data, ' ');
	else
		while ((data->flags.padding)--)
			ft_write_buffer(data, padchr);
	print_precision(data);
	specifier_handler(data, args, spcfr);
}

static void	process_flag_space(int spcfr, t_pf_data *data, va_list *args,
	char padchr)
{
	if (data->flags.is_ptr_nil)
		while ((data->flags.padding)--)
			ft_write_buffer(data, ' ');
	else
		while ((data->flags.padding)--)
			ft_write_buffer(data, padchr);
	if (data->flags.sign)
		ft_write_buffer(data, data->flags.sign);
	if (data->flags.prefix[0])
		ft_write_buffer(data, data->flags.prefix[0]);
	if (data->flags.prefix[1])
		ft_write_buffer(data, data->flags.prefix[1]);
	print_precision(data);
	specifier_handler(data, args, spcfr);
}

static void	print_arg(int spcfr, t_pf_data *data, va_list *args)
{
	if (data->flags.sign)
		ft_write_buffer(data, data->flags.sign);
	if (data->flags.prefix[0])
		ft_write_buffer(data, data->flags.prefix[0]);
	if (data->flags.prefix[1])
		ft_write_buffer(data, data->flags.prefix[1]);
	print_precision(data);
	specifier_handler(data, args, spcfr);
}

static void	print_precision(t_pf_data *data)
{
	while (data->flags.precisionlen)
	{
		ft_write_buffer(data, '0');
		(data->flags.precisionlen)--;
	}
}
