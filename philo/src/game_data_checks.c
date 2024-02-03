/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_data_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 11:55:52 by xamayuel          #+#    #+#             */
/*   Updated: 2024/02/03 23:29:06 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_all_numeric(int argn, char *argv[]);

int	ft_valid_input(int argn, char **argv)
{
	int	cont;

	cont = 1;
	if (argn < 5 || argn > 6)
		ft_report_error(ERR_N_ARGS);
	if (check_all_numeric(argn, argv) == FALSE)
		ft_report_error(ERR_NO_NUMBERS);
	while (cont < 5)
	{
		if (ft_atoi(argv[cont++]) == 0)
			ft_report_error(ERR_ZERO);
		if (cont > 1 && ft_atoi(argv[cont++]) <= 60)
			ft_report_error(ERR_MINIMUM);
	}
	if (argn == 6)
	{
		if (ft_atoi(argv[cont++]) == 0)
			ft_report_error(ERR_ZERO);
	}
	return (TRUE);
}

static int	check_all_numeric(int argn, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < argn)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
			{
				ft_report_error(ERR_NONUMERIC);
				return (FALSE);
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}
