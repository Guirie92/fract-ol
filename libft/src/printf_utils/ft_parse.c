/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 11:20:45 by guillsan          #+#    #+#             */
/*   Updated: 2025/11/29 21:58:56 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_flags_handler.h"

int	specifier_handler(t_pf_data *data, va_list *args, int spcfr)
{
	if (spcfr == 'c')
		ft_process_char(data, args);
	else if (spcfr == 's')
		ft_process_str(data, args);
	else if (spcfr == 'p')
		ft_process_ptr(data, args);
	else if (spcfr == 'd' || spcfr == 'i')
		ft_process_int(data, args);
	else if (spcfr == 'u')
		ft_process_uint(data, args, EBASE_10);
	else if (spcfr == 'o')
		ft_process_uint(data, args, EBASE_8);
	else if (spcfr == 'x')
		ft_process_uint(data, args, EBASE_16LC);
	else if (spcfr == 'X')
		ft_process_uint(data, args, EBASE_16UC);
	else
		return (EINVALID);
	return (EVALID);
}

static int	check_specifier(char const **fmt, t_pf_data *data, va_list *args)
{
	data->is_writing_mode = TRUE;
	data->has_flag = FALSE;
	if (specifier_handler(data, args, **fmt))
	{
		(*fmt)++;
		return (EVALID);
	}
	return (EINVALID);
}

/*
 * Flag syntax:
 * %[argument$][flags][width][.precision][length modifier]conversion
 * Linux Manual:
 * https://man7.org/linux/man-pages/man3/printf.3.html
 */
static int	check_flags(char const **fmt, t_pf_data *data, va_list *args)
{
	char const	*str;

	str = *fmt;
	data->is_writing_mode = FALSE;
	ft_reset_flags(data);
	while (*str && ft_strchr(FLAGS, *str))
	{
		ft_update_flags(&str, data);
		str++;
	}
	data->has_flag = TRUE;
	ft_compute_flag_precedence(data);
	ft_compute_width(&str, data);
	ft_compute_precision(&str, data);
	*fmt = str;
	data->rcode = check_for_valid_specifier(&str);
	if (data->rcode == EINVALID)
		return (EINVALID);
	else if (data->rcode == ENULL)
		return (ENULL);
	ft_evaluate_flags(&str, data, args);
	ft_process_valid_format(&str, data, args);
	*fmt = str;
	return (data->rcode);
}

int	ft_parse(t_pf_data *data, char const *fmt, va_list *args)
{
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			if (*fmt == '%')
			{
				ft_write_buffer(data, *fmt++);
				continue ;
			}
			if (check_specifier(&fmt, data, args))
				continue ;
			data->rcode = check_flags(&fmt, data, args);
			if (data->rcode == EINVALID)
				ft_process_invalid_format(*fmt, data);
			else if (data->rcode == ENULL)
				return (ft_flush_buffer(data, data->buflen), -1);
			else
				continue ;
		}
		ft_write_buffer(data, *fmt++);
	}
	ft_flush_buffer(data, data->buflen);
	return (data->count);
}
