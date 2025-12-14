/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_arglen.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:09:05 by guillsan          #+#    #+#             */
/*   Updated: 2025/11/29 21:58:56 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_flags_handler.h"

static int	extract_len(t_pf_data *data, va_list *args, int specifier);

int	ft_calculate_arglen(int spcfr, t_pf_data *data, va_list *args)
{
	va_list	args_tmp;
	int		len;

	va_copy(args_tmp, *args);
	len = extract_len(data, &args_tmp, spcfr);
	va_end(args_tmp);
	return (len);
}

static int	extract_len(t_pf_data *data, va_list *args, int spcfr)
{
	int	len;

	len = 0;
	if (spcfr == 'c')
		len = ft_process_char(data, args);
	else if (spcfr == 's')
		len = ft_process_str(data, args);
	else if (spcfr == 'p')
		len = ft_process_ptr(data, args);
	else if (spcfr == 'd' || spcfr == 'i')
		len = ft_process_int(data, args);
	else if (spcfr == 'u')
		len = ft_process_uint(data, args, EBASE_10);
	else if (spcfr == 'o')
		len = ft_process_uint(data, args, EBASE_8);
	else if (spcfr == 'x')
		len = ft_process_uint(data, args, EBASE_16LC);
	else if (spcfr == 'X')
		len = ft_process_uint(data, args, EBASE_16UC);
	return (len);
}
