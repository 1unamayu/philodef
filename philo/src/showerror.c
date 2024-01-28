/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   description.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:22:19 by xamayuel          #+#    #+#             */
/*   Updated: 2022/10/17 23:22:35 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

/**
 * @brief Show at stderr the program required arguments.
 * 
 */
void	show_error_arguments(void)
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
