/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_ptr_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 21:19:07 by guillsan          #+#    #+#             */
/*   Updated: 2025/11/29 22:01:04 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_flags_handler.h"

static int	write_nil(t_pf_data *data, const char *str_null);

int	ft_process_char(t_pf_data *data, va_list *args)
{
	int	arg;
	int	count;

	arg = va_arg(*args, int);
	count = 1;
	if (data->is_writing_mode)
		ft_write_buffer(data, arg);
	return (count);
}

int	ft_process_str(t_pf_data *data, va_list *args)
{
	size_t	len;
	char	*arg;
	char	*str;

	arg = va_arg(*args, char *);
	str = arg;
	if (!str)
		return (ft_write_null(data, NULL_STR));
	len = ft_calc_write_str(data, str);
	return (len);
}

int	ft_process_ptr(t_pf_data *data, va_list *args)
{
	void				*ptr;
	unsigned long long	n;
	int					len;
	int					idx;

	idx = 0;
	ptr = va_arg(*args, void *);
	if (!ptr)
		return (write_nil(data, NIL_STR));
	n = (unsigned long long)ptr;
	if (data->has_flag)
	{
		data->flags.prefix[0] = ADDR_PREFIX[0];
		data->flags.prefix[1] = ADDR_PREFIX[1];
		data->flags.prefixlen += 2;
	}
	else
	{
		(data->tempbuf)[idx++] = ADDR_PREFIX[0];
		(data->tempbuf)[idx++] = ADDR_PREFIX[1];
	}
	ft_ui64toa_base_print(n, EBASE_16LC, &(data->tempbuf)[idx]);
	len = ft_calclen_write(data, data->tempbuf);
	return (len);
}

static int	write_nil(t_pf_data *data, const char *str_nil)
{
	int	len;

	data->flags.is_ptr_nil = TRUE;
	len = ft_calclen_write(data, str_nil);
	return (len);
}
