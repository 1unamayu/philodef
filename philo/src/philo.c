/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:30:02 by xamayuel          #+#    #+#             */
/*   Updated: 2024/01/28 21:44:50 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void ft_set_game(char *argv[], int argn, t_game *game)
{
	game->total_persons = ft_atoi(argv[1]);
	game->env.death = 0;
	game->env.fat = 0;
	game->env.time_die = ft_atoi(argv[2]);
	game->env.time_eat= ft_atoi(argv[3]);
	game->env.time_sleep = ft_atoi(argv[4]);
	game->env.max_meals = 0;
}

int	main(int argn, char *argv[])
{
	t_game	game;

	if (argn < 5 || argn > 6)
		return (report_error(ERR_N_ARGS));
	if (check_all_numeric(argn, argv) == FALSE)
		return (report_error(ERR_NO_NUMBERS));
	ft_set_game(argv,argn, &game);
	
	return (0);
}