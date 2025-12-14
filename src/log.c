/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:10:41 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/13 01:11:50 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_log(int fd, char *msg)
{
	ft_printf_fd(fd, msg);
}

void	exit_message(int fd, char *msg)
{
	ft_printf_fd(fd, msg);
	exit(EXIT_FAILURE);
}
