/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 22:21:40 by guillsan          #+#    #+#             */
/*   Updated: 2025/11/29 21:58:56 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_reset_flags(t_pf_data *data)
{
	ft_bzero(&data->flags, sizeof(t_flags));
	data->flags.width = -1;
	data->flags.precision = -1;
}

void	ft_compute_width(char const **str, t_pf_data *data)
{
	int	c;

	c = (int)(**str);
	if (ft_isdigit(c))
		data->flags.width = 0;
	while (ft_isdigit(c))
	{
		data->flags.width = data->flags.width * 10 + (c - '0');
		(*str)++;
		c = (int)(**str);
	}
}

void	ft_compute_precision(char const **str, t_pf_data *data)
{
	int	c;

	c = (int)(**str);
	if (c != '.')
		return ;
	(*str)++;
	c = (int)(**str);
	data->flags.precision = 0;
	while (ft_isdigit(c))
	{
		data->flags.precision = data->flags.precision * 10 + (c - '0');
		(*str)++;
		c = (int)(**str);
	}
}

void	ft_compute_flag_precedence(t_pf_data *data)
{
	if (data->flags.minus)
		data->flags.zero = 0;
	if (data->flags.plus)
		data->flags.space = 0;
}

void	ft_update_flags(char const **str, t_pf_data *data)
{
	unsigned char	c;

	c = (unsigned char)(**str);
	if (c == '-')
		data->flags.minus = 1;
	else if (c == '0')
		data->flags.zero = 1;
	else if (c == '#')
		data->flags.hash = 1;
	else if (c == ' ')
		data->flags.space = 1;
	else if (c == '+')
		data->flags.plus = 1;
}
