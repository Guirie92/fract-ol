/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:01:31 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/15 16:34:16 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <stdint.h>
# include "ft_printf.h"

double	ft_atodbl(const char *s);
int		ft_isdigit(int c);
int		ft_isspace(int c);
void	*ft_memset(void *s, int c, size_t n);
int		ft_mod(int a, int b);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_itoa_buffer(int n, char *buf);
void	ft_lltoa_buffer(long long n, char *buf);
void	ft_ulltoa_buffer(unsigned long long n, char *buf);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	ft_ftoa_buffer(float nb, char *buf, int decimals);


#endif /* LIBFT_H */