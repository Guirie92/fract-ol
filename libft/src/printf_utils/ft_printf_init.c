/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 21:54:06 by guillsan          #+#    #+#             */
/*   Updated: 2025/11/29 22:11:50 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_init(t_pf_data *data)
{
	data->buf[0] = 0;
	data->tempbuf[0] = 0;
	data->buflen = 0;
	data->count = 0;
	data->rcode = 0;
	data->fd = 1;
	data->is_writing_mode = FALSE;
	data->has_flag = FALSE;
	data->flags.minus = 0;
	data->flags.zero = 0;
	data->flags.plus = 0;
	data->flags.space = 0;
	data->flags.hash = 0;
	data->flags.width = -1;
	data->flags.precision = -1;
	data->flags.specifier = 0;
	data->flags.sign = '\0';
	data->flags.prefix[0] = '\0';
	data->flags.prefix[1] = '\0';
	data->flags.prefixlen = 0;
	data->flags.padding = 0;
	data->flags.precisionlen = 0;
	data->flags.is_ptr_nil = FALSE;
}
