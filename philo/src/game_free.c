/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 23:39:27 by xamayuel          #+#    #+#             */
/*   Updated: 2024/02/03 22:09:50 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

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
		pthread_mutex_destroy(&game->philos[i].m_npc_death);
	}
	free(game->forks);
	free(game->philos);
}
