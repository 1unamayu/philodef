/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_show.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:22:19 by xamayuel          #+#    #+#             */
/*   Updated: 2024/02/03 23:30:20 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	ft_error(char *string);
static void	ft_show_error_arguments(void);

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

static int	ft_error(char *string)
{
	while (*string)
		write(2, string++, 1);
	return (FALSE);
}

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
