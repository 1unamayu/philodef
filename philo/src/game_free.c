/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 23:39:27 by xamayuel          #+#    #+#             */
/*   Updated: 2024/02/04 14:13:09 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Functions for freeing resources used by the philosophers game.
 * 
 * This file contains functions for freeing resources used by the game. 
 * It includes functions for destroying mutexes and freeing memory allocated for 
 * philosopher instances and fork mutexes.
 * 
 */

#include <philosophers.h>

/**
 * @brief Frees resources used by the game.
 * 
 * This function frees resources used by the philosophers game. It destroys 
 * mutexes used for synchronization and frees memory allocated for philosopher 
 * instances and fork mutexes.
 * 
 * @param game Pointer to the game structure.
 */
void	ft_free_game(t_game *game)
{
	int	i;

	pthread_mutex_destroy(&game->env.m_screen);
	pthread_mutex_destroy(&game->env.m_main);
	pthread_mutex_destroy(&game->env.m_readwrite);
	i = -1;
	while (++i < game->num_npcs)
	{
		pthread_mutex_destroy(&game->forks[i]);
		pthread_mutex_destroy(&game->npcs[i].m_npc_death);
	}
	free(game->forks);
	free(game->npcs);
}
