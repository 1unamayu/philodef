/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   report.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 14:39:17 by xamayuel          #+#    #+#             */
/*   Updated: 2024/01/28 21:35:48 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


/**
 * @brief Report an error with a corresponding error message.
 * 
 * This function takes an error type as an argument and displays a
 * corresponding error message in red text to the stderr output.
 * Provide additional instructions or details.
 * 
 * @param type The error type to be reported.
 * 
 * @return Returns -1 to indicate that an error has occurred.
 */
int	report_error(int type)
{
	ft_error(RED);
	if (type == ERR_N_ARGS)
		ft_error("Please introduce a correct number of arguments (4/5)\n");
	if (type == ERR_NO_NUMBERS)
		ft_error("Please introduce only numbers as arguments\n");
	if (type == ERR_ZERO)
		ft_error("Zeros are not allowed in any field\n");
	if (type == ERR_MALLOC)
		ft_error(RED"Error allocating memory!!\n");
	if (type == ERR_MUTEX)
		ft_error("Mutex error!!\n");
	ft_error(WHITE);
	if (type == ERR_N_ARGS || type == ERR_NO_NUMBERS || type == ERR_ZERO)
		show_error_arguments();
	return (-1);
}

/**
 * @brief Display an error message to the standard error output (stderr).
 * 
 * This function takes a string as an argument and 
 * write it to the standard error output (stderr). It is used to display
 * error messages during program execution.
 * 
 * @param string The error message to be displayed.
 * 
 * @return Returns always FALSE.
 */
int	ft_error(char *string)
{
	while (*string)
		write(2, string++, 1);
	return (FALSE);
}
