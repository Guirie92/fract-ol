/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 20:53:07 by guillsan          #+#    #+#             */
/*   Updated: 2025/11/29 23:52:45 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <stddef.h>
# include <limits.h>
# include <stdint.h>
# include "libft.h"

/* Constants */
# define SPECIFIERS    "cspdiuoxX"
# define FLAGS         "#+ -0"
# define BASE_8        "01234567"
# define BASE_10       "0123456789"
# define BASE_16LC     "0123456789abcdef"
# define BASE_16UC     "0123456789ABCDEF"

/* Const Strings */
# define NULL_STR      "(null)"
# define NIL_STR       "(nil)"
# define INT_MIN_STR   "2147483648"

/* Prefix */
# define ADDR_PREFIX   "0x"

# define FD            1
# define BUFFER_SIZE   1024
# define TEMP_BUF_SIZE 64
# define TRUE          1
# define FALSE         0

typedef struct s_flags
{
	int		minus;
	int		zero;
	int		plus;
	int		space;
	int		hash;
	ssize_t	width;
	ssize_t	precision;
	char	specifier;
	char	sign;
	char	prefix[2];
	int		prefixlen;
	int		padding;
	int		precisionlen;
	int		is_ptr_nil;
}	t_flags;

typedef enum e_pf_rcode
{
	EINVALID = 0,
	EVALID = 1,
	ENULL = 2,
}	t_pf_rcode;

typedef struct s_pf_data
{
	char		buf[BUFFER_SIZE];
	char		tempbuf[TEMP_BUF_SIZE];
	size_t		buflen;
	size_t		count;
	t_flags		flags;
	t_pf_rcode	rcode;
	int			is_writing_mode;
	int			has_flag;
	int			fd;
}	t_pf_data;

typedef enum e_pf_base
{
	EBASE_8 = 0,
	EBASE_10 = 1,
	EBASE_16LC = 2,
	EBASE_16UC = 3,
}	t_pf_base;

int		ft_printf(char const *fmt, ...);
int		ft_printf_fd(int fd, char const *fmt, ...);
void	ft_init(t_pf_data *data);
int		ft_calclen_write(t_pf_data *data, const char *str);
void	ft_write_buffer(t_pf_data *data, int c);
void	ft_flush_buffer(t_pf_data *data, size_t len);

/* ft_parse.c */
int		ft_parse(t_pf_data *data, char const *fmt, va_list *args);
int		specifier_handler(t_pf_data *data, va_list *args, int spcfr);

/* utils */
int		ft_ui64toa_base_print(unsigned long long n,
			t_pf_base e_base, char *buffer);
int		ft_itoa_print(int n, char *buf, t_pf_data *data);
char	*ft_strchr(const char *s, int c);
void	ft_bzero(void *s, size_t n);

#endif /* FT_PRINTF_H */