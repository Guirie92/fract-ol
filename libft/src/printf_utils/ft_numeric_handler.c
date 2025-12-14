/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numeric_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 21:21:02 by guillsan          #+#    #+#             */
/*   Updated: 2025/11/29 23:55:24 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_process_int(t_pf_data *data, va_list *args)
{
	int	arg;
	int	len;

	arg = va_arg(*args, int);
	if (arg == 0 && data->has_flag && data->flags.precision == 0)
		return (0);
	ft_itoa_print(arg, data->tempbuf, data);
	len = ft_calclen_write(data, data->tempbuf);
	return (len);
}

int	ft_process_uint(t_pf_data *data, va_list *args, t_pf_base base)
{
	unsigned int	arg;
	int				len;

	arg = va_arg(*args, unsigned int);
	if (arg == 0 && data->has_flag && data->flags.precision == 0
		&& !(data->flags.specifier == 'o' && data->flags.hash == 1))
		return (0);
	ft_ui64toa_base_print(arg, base, data->tempbuf);
	len = ft_calclen_write(data, data->tempbuf);
	return (len);
}
