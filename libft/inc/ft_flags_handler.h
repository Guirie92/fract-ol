/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_handler.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 20:53:07 by guillsan          #+#    #+#             */
/*   Updated: 2025/11/29 23:50:30 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FLAGS_HANDLER_H
# define FT_FLAGS_HANDLER_H

# include "ft_printf.h"

/* ft_char_handler.c */

int		ft_process_char(t_pf_data *data, va_list *args);
int		ft_process_str(t_pf_data *data, va_list *args);
int		ft_process_ptr(t_pf_data *data, va_list *args);

/* ft_numeric_handler.c */

int		ft_process_int(t_pf_data *data, va_list *args);
int		ft_process_uint(t_pf_data *data, va_list *args, t_pf_base base);

/* ft_flags_handler.c */

void	ft_reset_flags(t_pf_data *data);
void	ft_update_flags(char const **str, t_pf_data *data);
void	ft_compute_width(char const **str, t_pf_data *data);
void	ft_compute_precision(char const **str, t_pf_data *data);
void	ft_compute_flag_precedence(t_pf_data *data);

/* ft_flag_utils.c */

int		ft_calc_write_str(t_pf_data *data, const char *str);
int		ft_write_null(t_pf_data *data, const char *str_null);
int		check_for_valid_specifier(char const **str);
void	ft_handle_ptr_sign_id(int spcfr, t_pf_data *data, va_list *args);

/* ft_valid_format.c */

void	ft_process_valid_format(char const **str, t_pf_data *data,
			va_list *args);

/* ft_invalid_format.c */

void	ft_process_invalid_format(char spcfr, t_pf_data *data);

/* ft_flag_evaluation.c */

void	ft_evaluate_flags(char const **str, t_pf_data *data, va_list *args);

/* ft_calculate_arglen.c */

int		ft_calculate_arglen(int spcfr, t_pf_data *data, va_list *args);

#endif /* FT_FLAGS_HANDLER_H */