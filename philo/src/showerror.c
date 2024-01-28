/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   showerror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 11:03:02 by xamayuel          #+#    #+#             */
/*   Updated: 2024/01/28 11:06:44 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>


static int	ft_error(const char *string)
{
	while (*string)
		write(2, string++, 1);
	return (FALSE);
}

static void	show_error_arguments(void)
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


int	ft_report_error(int error_type)
{
	ft_error(RED);
	if (error_type == ERR_N_ARGS)
		ft_error("Please introduce a correct number of arguments (4/5)\n");
	if (error_type == ERR_NO_NUMBERS)
		ft_error("Please introduce only numbers as arguments\n");
	if (error_type == ERR_ZERO)
		ft_error("Zeros are not allowed in any field\n");
	if (error_type == ERR_MALLOC)
		ft_error(RED"Error allocating memory!!\n");
	if (error_type == ERR_MUTEX)
		ft_error("Mutex error!!\n");
	ft_error(WHITE);
	if (error_type == ERR_N_ARGS || error_type == ERR_NO_NUMBERS || error_type == ERR_ZERO)
		show_error_arguments();
	return (-1);
}

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