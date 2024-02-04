/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:30:02 by xamayuel          #+#    #+#             */
/*   Updated: 2024/02/04 13:07:15 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief The main function for running the philosophers game.
 * 
 * This function serves as the entry point for running the philosophers game.
 * It validates the input arguments, initializes the game, starts the game 
 * simulation, and finally frees the allocated memory before exiting.
 * 
 * @param argn Number of arguments passed to the program.
 * @param argv Array of strings containing the arguments passed to the program.
 * @return Returns 0 upon successful execution.
 */
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
