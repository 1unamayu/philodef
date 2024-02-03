/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:30:02 by xamayuel          #+#    #+#             */
/*   Updated: 2024/02/03 22:09:03 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	main(int argn, char **argv)
{
	t_game		game;

	ft_valid_input(argn, argv);
	ft_set_game(argv, argn, &game);
	ft_start_game(&game);
	ft_free_game(&game);
	return (0);
}
