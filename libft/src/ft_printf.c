/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 21:00:02 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/02 06:11:27 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(char const *fmt, ...)
{
	t_pf_data	data;
	va_list		args;
	int			res;

	if (!fmt)
		return (-1);
	ft_init(&data);
	va_start(args, fmt);
	res = ft_parse(&data, fmt, &args);
	va_end(args);
	return (res);
}

int	ft_printf_fd(int fd, char const *fmt, ...)
{
	t_pf_data	data;
	va_list		args;
	int			res;

	if (!fmt)
		return (-1);
	ft_init(&data);
	data.fd = fd;
	va_start(args, fmt);
	res = ft_parse(&data, fmt, &args);
	va_end(args);
	return (res);
}

int	ft_calclen_write(t_pf_data *data, const char *str)
{
	int	len;

	len = 0;
	if (data->is_writing_mode)
	{
		while (*str)
		{
			ft_write_buffer(data, *str++);
			len++;
		}
	}
	else
		while (*str++)
			len++;
	return (len);
}

void	ft_write_buffer(t_pf_data *data, int c)
{
	if (data->buflen >= BUFFER_SIZE)
		ft_flush_buffer(data, data->buflen);
	(data->buf)[(data->buflen)++] = c;
	(data->count)++;
}

void	ft_flush_buffer(t_pf_data *data, size_t len)
{
	ssize_t	bytes_written;

	bytes_written = write(data->fd, data->buf, len);
	(void)bytes_written;
	data->buflen = 0;
}
