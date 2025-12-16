/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 22:19:57 by guillsan          #+#    #+#             */
/*   Updated: 2025/12/15 22:57:19 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fractol.h"

static int	validate_args(int ac, char **av, t_fract *fract)
{
	if (ac == 2)
	{
		if (ft_strncmp(av[1], MANDELBROT_NAME, MANDELBROT_NAME_LEN) == 0)
		{
			fract->fract_mode = E_MANDELBROT;
			return (E_SUCCESS);
		}
		else if (ft_strncmp(av[1], BURNING_NAME, BURNING_NAME_LEN) == 0)
		{
			fract->fract_mode = E_BURNING;
			return (E_SUCCESS);
		}
	}
	if (ac == 4)
	{
		if (ft_strncmp(av[1], JULIA_NAME, JULIA_NAME_LEN) == 0)
		{
			if (parse_args(fract, av) == E_SUCCESS)
				return (E_SUCCESS);
		}
	}
	return (EERROR);
}

int	main(int ac, char **av)
{
	t_fract	fract;
	int		rcode;

	ft_memset(&fract, 0, sizeof(fract));
	fract.julia_r = JULIA_DEFAULT_R_VAL;
	fract.julia_i = JULIA_DEFAULT_I_VAL;
	if (ac != 2 && ac != 4)
		exit_message(STDERR_FILENO, USAGE_MESSAGE);
	if (validate_args(ac, av, &fract) == EERROR)
		exit_message(STDERR_FILENO, USAGE_MESSAGE);
	rcode = init(&fract);
	if (rcode == E_MEM_ERROR)
	{
		perror(CLR_RED "Error" CLR_RST);
		free_res(&fract, EXIT_FAILURE);
	}
	render(&fract);
	events_init(&fract);
	ft_log(STDOUT_FILENO, HELP_INFO);
	mlx_loop(fract.mlx);
	return (0);
}
