/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 11:55:52 by xamayuel          #+#    #+#             */
/*   Updated: 2024/01/28 21:31:57 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Check if all command-line arguments are numeric.
 * 
 * This function iterates through the command-line arguments starting from 1,
 * checking each character in the argument strings.
 * If any character is not a numeric character ('0' to '9'),
 * it displays an error message and returns FALSE.
 * 
 * @param argn The number of command-line arguments.
 * @param argv An array of strings containing the command-line arguments.
 * 
 * @return Returns TRUE if all arguments are numeric, otherwise FALSE.
 */
int	check_all_numeric(int argn, char *argv[])
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
				ft_error("\033[0;31mArgument not numeric found!!\033[0;37m\n");
				return (FALSE);
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}


