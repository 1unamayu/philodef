/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_data_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 11:55:52 by xamayuel          #+#    #+#             */
/*   Updated: 2024/02/07 19:16:11 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Functions for validating input arguments for the philosophers game.
 * 
 * This file contains functions for validating input arguments provided to 
 * the philosophers game. It includes functions to check if the correct number 
 * of arguments is provided, if all arguments are numeric, and if certain 
 * conditions regarding the arguments are met.
 * 
 */

#include "philosophers.h"

static int	check_all_numeric(int argn, char *argv[]);

/**
 * @brief Validates the input arguments provided to the philosophers game.
 * 
 * This function validates the input arguments provided. 
 * It checks if the correct number of arguments is provided, if all arguments 
 * are numeric, and if certain conditions regarding the arguments 
 * are met. It reports an error and exits if any validation fails.
 * 
 * @param argn Number of arguments passed to the program.
 * @param argv Array of strings containing the arguments passed to the program.
 * @return Returns TRUE if the input arguments are valid.
 */
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
	}
	if (argn == 6)
	{
		if (ft_atoi(argv[cont++]) == 0)
			ft_report_error(ERR_ZERO);
	}
	return (TRUE);
}

/**
 * @brief Checks if all arguments are numeric.
 * 
 * This function checks if all arguments provided to the program are numeric. 
 * It iterates through each argument and each character within the argument 
 * to ensure that only numeric characters are present.
 * 
 * @param argn Number of arguments passed to the program.
 * @param argv Array of strings containing the arguments passed to the program.
 * @return Returns TRUE if all arguments are numeric, otherwise returns FALSE.
 */
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
