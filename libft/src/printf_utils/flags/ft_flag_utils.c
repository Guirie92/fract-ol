/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 21:56:11 by guillsan          #+#    #+#             */
/*   Updated: 2025/11/29 21:58:56 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_flags_handler.h"

static int	write_str(t_pf_data *data, const char *str, int len);

int	ft_calc_write_str(t_pf_data *data, const char *str)
{
	int	len;

	len = 0;
	if (data->is_writing_mode)
		len = write_str(data, str, len);
	else
		while (*str++)
			len++;
	return (len);
}

static int	write_str(t_pf_data *data, const char *str, int len)
{
	if (data->flags.precision >= 0)
	{
		while (*str && data->flags.precision--)
		{
			ft_write_buffer(data, *str++);
			len++;
		}
	}
	else
	{
		while (*str)
		{
			ft_write_buffer(data, *str++);
			len++;
		}
	}
	return (len);
}

int	ft_write_null(t_pf_data *data, const char *str_null)
{
	int	len;

	len = 0;
	if (data->has_flag != TRUE || data->flags.precision == -1
		|| data->flags.precision >= 6)
		len = ft_calclen_write(data, str_null);
	return (len);
}

void	ft_handle_ptr_sign_id(int spcfr, t_pf_data *data, va_list *args)
{
	va_list	args_tmp;
	void	*arg;

	if (spcfr != 'p')
		return ;
	va_copy(args_tmp, *args);
	arg = va_arg(args_tmp, void *);
	if (arg == NULL)
	{
		data->flags.precision = 0;
		va_end(args_tmp);
		return ;
	}
	if (data->flags.plus)
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

int	check_for_valid_specifier(char const **str)
{
	if (**str == '\0')
		return (ENULL);
	if (!ft_strchr(SPECIFIERS, **str))
		return (EINVALID);
	return (EVALID);
}
