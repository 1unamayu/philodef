/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:24:32 by xamayuel          #+#    #+#             */
/*   Updated: 2024/02/04 13:48:35 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Functions for setting up the philosophers game environment.
 * 
 * This file contains functions for setting up the environment for the 
 * philosophers game. It includes functions for reading input data, initializing 
 * mutexes, setting up philosopher instances, and creating threads to simulate 
 * philosopher behavior.
 * 
 */

#include "philosophers.h"

static void	ft_set_mutex(t_game *game);
static void	ft_read_input(t_game *game, char **input, int argn);
static void	ft_set_npcs(t_game *game);
static void	ft_set_threads(t_game *game);

/**
 * @brief Sets up the game environment using the provided input data.
 * 
 * This function sets up the game environment by reading the input data, 
 * initializing mutexes, setting up philosopher instances, and creating threads 
 * to simulate philosopher behavior.
 * 
 * @param data Array of strings containing input data provided to the program.
 * @param argc Number of arguments passed to the program.
 * @param game Pointer to the game structure.
 */
void	ft_set_game(char **data, int argc, t_game *game)
{
	ft_read_input(game, data, argc);
	ft_set_mutex(game);
	ft_set_npcs(game);
	ft_set_threads(game);
}

/**
 * @brief Reads the input data and initializes the game environment.
 * 
 * This function reads the input data provided to the program, initializes 
 * the game environment with the provided parameters, and stores them in the 
 * game structure.
 * 
 * @param game Pointer to the game structure.
 * @param input Array of strings containing input data provided to the program.
 * @param argn Number of arguments passed to the program.
 */
static void	ft_read_input(t_game *game, char **input, int argn)
{
	game->num_npcs = ft_atoi(input[1]);
	game->env.death = 0;
	game->env.number_full = 0;
	game->env.time_to_die = ft_atoi(input[2]);
	game->env.time_eating = ft_atoi(input[3]);
	game->env.time_sleeping = ft_atoi(input[4]);
	game->env.t_start = ft_current_time();
	game->env.number_npc_meals = 0;
	if (argn == 6)
		game->env.number_npc_meals = ft_atoi(input[5]);
}

/**
 * @brief Initializes mutexes for thread synchronization.
 * 
 * This function initializes mutexes for thread synchronization in the game.
 * It initializes mutexes for screen output, main thread synchronization,  
 * and for controlling read-write access.
 * 
 * @param game Pointer to the game structure.
 */
static void	ft_set_mutex(t_game *game)
{
	int	i;

	pthread_mutex_init(&game->env.m_screen, NULL);
	pthread_mutex_init(&game->env.m_main, NULL);
	pthread_mutex_init(&game->env.m_readwrite, NULL);
	game->forks = malloc(sizeof(pthread_mutex_t) * game->num_npcs);
	if (!game->forks)
		ft_report_error(ERR_MALLOC);
	i = -1;
	while (++i < game->num_npcs)
	{
		if (pthread_mutex_init(&game->forks[i], NULL))
			ft_report_error(ERR_MUTEX);
	}
}

/**
 * @brief Sets up philosopher instances.
 * 
 * This function sets up philosopher instances based on the number  
 * of philosophers provided in the game environment. 
 * It initializes each philosopher's attributes and assigns mutexes 
 * for fork access.
 * 
 * @param game Pointer to the game structure.
 */
static void	ft_set_npcs(t_game *game)
{
	int	i;

	game->npcs = malloc(sizeof(t_npc) * game->num_npcs);
	if (!game->npcs)
		ft_report_error(ERR_MALLOC);
	i = -1;
	while (++i < game->num_npcs)
	{
		game->npcs[i].id_npc = i + 1;
		game->npcs[i].meals_eaten = 0;
		game->npcs[i].t_last_meal = game->env.t_start;
		game->npcs[i].env = &game->env;
		game->npcs[i].m_lfork = &game->forks[(game->npcs[i].id_npc - 1)];
		game->npcs[i].m_rfork = &game->forks[(game->npcs[i].id_npc) \
															% game->num_npcs];
		if (game->num_npcs == 1)
			game->npcs[i].m_rfork = NULL;
		pthread_mutex_init(&game->npcs[i].m_npc_death, NULL);
	}
}

/**
 * @brief Creates threads to simulate philosopher behavior.
 * 
 * This function creates threads to simulate philosopher behavior. It creates a 
 * thread for each philosopher instance and a separate thread for the doctor's 
 * health monitoring.
 * 
 * @param game Pointer to the game structure.
 */
static void	ft_set_threads(t_game *game)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&game->env.m_main);
	if (pthread_create(&game->doctor, NULL, &ft_doctor_health, game))
		ft_report_error(ERR_MALLOC);
	while (++i < game->num_npcs)
	{
		if (pthread_create(&game->npcs[i].id_thread, NULL, &ft_npc_life, \
				&game->npcs[i]))
			ft_report_error(ERR_MALLOC);
	}
	pthread_mutex_unlock(&game->env.m_main);
}
