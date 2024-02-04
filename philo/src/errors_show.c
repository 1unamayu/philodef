/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_show.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:22:19 by xamayuel          #+#    #+#             */
/*   Updated: 2024/02/04 13:50:25 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Functions for reporting and displaying errors in the  game.
 * 
 * This file contains functions for reporting and displaying errors that  
 * may occur during the execution of the philosophers game. 
 * It includes functions for reporting various types of errors, displaying error 
 * messages, and providing guidance on correct usage of command-line arguments.
 * 
 */

#include <philosophers.h>

static int	ft_error(char *string);
static void	ft_show_error_arguments(void);

/**
 * @brief Reports errors encountered during the execution of the game.
 * 
 * This function reports errors encountered during the execution of the 
 * philosophers game. It takes an error type as an argument and displays  
 * an appropriate error message based on the type of error encountered. 
 * If the error type is related to invalid command-line arguments, 
 * it also displays guidance on correct usage.
 * 
 * @param type The type of error encountered.
 */
void	ft_report_error(int type)
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
	if (type == ERR_NONUMERIC)
		ft_error("Argument not numeric found!!\n");
	if (type == ERR_MINIMUM)
		ft_error("Time argument must be bigger than 60ms!!\n");
	ft_error(WHITE);
	if (type > ERR_MUTEX)
		ft_show_error_arguments();
	exit(0);
}

/**
 * @brief Displays an error message.
 * 
 * This function displays an error message by printing the provided string 
 * to the standard error output (stderr).
 * 
 * @param string The error message to be displayed.
 * @return Returns FALSE if an error occurs while displaying the message.
 */
static int	ft_error(char *string)
{
	while (*string)
		write(2, string++, 1);
	return (FALSE);
}

/**
 * @brief Displays guidance on correct usage of command-line arguments.
 * 
 * This function displays guidance on correct usage of command-line arguments 
 * when certain errors related to invalid arguments are encountered.
 */
static void	ft_show_error_arguments(void)
{
	ft_error("\n"WHITE);
	ft_error("Following arguments must be defined:\n");
	ft_error("(only numeric characters)\n");
	ft_error(CYAN"\n\t\t\tnumber of philosophers:");
	ft_error(WHITE" Nº of philosophers at the table");
	ft_error(CYAN"\n\t\t\t\t   time to die:");
	ft_error(WHITE" Time to die after eat, in miliseconds");
	ft_error(CYAN"\n\t\t\t\t   time to eat:");
	ft_error(WHITE" Time eating, in miliseconds");
	ft_error(CYAN"\n\t\t\t\t time to sleep:");
	ft_error(WHITE" Time sleeping, in miliseconds");
	ft_error(CYAN"\n     number_of_times_each_philosopher_must_eat:");
	ft_error(WHITE" Nº of time each");
	ft_error("philosopher mus eat before the program ends (OPTIONAL)");
	ft_error("\n");
}
