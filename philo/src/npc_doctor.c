/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_doctor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:10:08 by xamayuel          #+#    #+#             */
/*   Updated: 2024/02/04 13:46:56 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Functions for monitoring the health of philosophers in the game.
 * 
 * This file contains functions for monitoring the health of philosophers 
 * in the philosophers game. It includes a function for a doctor thread that 
 * continuously checks for philosopher's health and terminates the game 
 * if a philosopher dies or if all philosophers have finished eating.
 * 
 */

#include <philosophers.h>

static void	ft_endgame(t_game *game);
static int	ft_check_death(t_npc *npc);

/**
 * @brief Monitors the health of philosophers.
 * 
 * This function represents a doctor thread that continuously monitors the 
 * health of philosophers in the game. It checks if any philosopher has 
 * died due to starvation or if all philosophers have finished eating. If 
 * so, it terminates the game by setting the appropriate flag in the game 
 * environment and returns.
 * 
 * @param args Pointer to the game structure.
 * @return Returns NULL upon termination of the doctor thread.
 */
void	*ft_doctor_health(void *args)
{
	t_game		*game;
	int			i;

	game = (t_game *) args;
	while (game->env.death == 0)
	{
		i = -1;
		while (++i < game->num_npcs)
		{
			if (ft_check_death(&game->npcs[i]))
			{
				ft_print(&game->npcs[i], "died");
				ft_endgame(game);
				return (NULL);
			}
		}
		if (game->env.number_npc_meals && \
				(game->env.number_full == game->num_npcs))
		{
			ft_endgame(game);
			return (NULL);
		}
		usleep(10);
	}
	return (NULL);
}

/**
 * @brief Checks if a philosopher has died due to starvation.
 * 
 * This function checks if a philosopher has died due to starvation by 
 * comparing the time since the philosopher's last meal with the maximum 
 * time allowed for starvation. It locks the read-write mutex to access 
 * the philosopher's attributes safely.
 * 
 * @param npc Pointer to the philosopher structure.
 * @return Returns 1 if the philosopher has died, otherwise returns 0.
 */
static int	ft_check_death(t_npc *npc)
{
	long long	hungry;

	pthread_mutex_lock(&npc->env->m_readwrite);
	hungry = ft_timestamp(npc->t_last_meal);
	if (hungry > npc->env->time_to_die)
	{
		pthread_mutex_unlock(&npc->env->m_readwrite);
		return (1);
	}
	pthread_mutex_unlock(&npc->env->m_readwrite);
	return (0);
}

/**
 * @brief Ends the game.
 * 
 * This function ends the game by setting the appropriate flag in the 
 * game environment to indicate the end of the game. It locks the 
 * read-write mutex to update the game environment safely.
 * 
 * @param game Pointer to the game structure.
 */
static void	ft_endgame(t_game *game)
{
	pthread_mutex_lock(&game->env.m_readwrite);
	game->env.death = 1;
	pthread_mutex_unlock(&game->env.m_readwrite);
}
