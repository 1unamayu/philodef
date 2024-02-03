/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:24:32 by xamayuel          #+#    #+#             */
/*   Updated: 2024/02/03 23:36:27 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_set_mutex(t_game *game);
static void	ft_read_input(t_game *game, char **input, int argn);
static void	ft_set_npcs(t_game *game);
static void	ft_set_threads(t_game *game);

void	ft_set_game(char **data, int argc, t_game *game)
{
	ft_read_input(game, data, argc);
	ft_set_mutex(game);
	ft_set_npcs(game);
	ft_set_threads(game);
}

static void	ft_read_input(t_game *game, char **input, int argn)
{
	game->num_npcs = ft_atoi(input[1]);
	game->env.death = 0;
	game->env.fat = 0;
	game->env.time_to_die = ft_atoi(input[2]);
	game->env.time_eating = ft_atoi(input[3]);
	game->env.time_sleeping = ft_atoi(input[4]);
	game->env.t_start = ft_current_time();
	game->env.number_npc_meals = 0;
	if (argn == 6)
		game->env.number_npc_meals = ft_atoi(input[5]);
}

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

static void	ft_set_npcs(t_game *game)
{
	int	i;

	game->philos = malloc(sizeof(t_npc) * game->num_npcs);
	if (!game->philos)
		ft_report_error(ERR_MALLOC);
	i = -1;
	while (++i < game->num_npcs)
	{
		game->philos[i].id_npc = i + 1;
		game->philos[i].meals_eaten = 0;
		game->philos[i].t_last_meal = game->env.t_start;
		game->philos[i].env = &game->env;
		game->philos[i].m_lfork = &game->forks[(game->philos[i].id_npc - 1)];
		game->philos[i].m_rfork = &game->forks[(game->philos[i].id_npc) \
															% game->num_npcs];
		if (game->num_npcs == 1)
			game->philos[i].m_rfork = NULL;
		pthread_mutex_init(&game->philos[i].m_npc_death, NULL);
	}
}

static void	ft_set_threads(t_game *game)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&game->env.m_main);
	if (pthread_create(&game->doctor, NULL, &ft_doctor_health, game))
		ft_report_error(ERR_MALLOC);
	while (++i < game->num_npcs)
	{
		if (pthread_create(&game->philos[i].id_thread, NULL, &ft_npc_life, \
				&game->philos[i]))
			ft_report_error(ERR_MALLOC);
	}
	pthread_mutex_unlock(&game->env.m_main);
}
