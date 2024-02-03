/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_doctor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:10:08 by xamayuel          #+#    #+#             */
/*   Updated: 2024/02/03 23:33:40 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static void	ft_endgame(t_game *game);
static int	ft_check_death(t_npc *philo);

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
			if (ft_check_death(&game->philos[i]))
			{
				ft_print(&game->philos[i], "died");
				ft_endgame(game);
				return (NULL);
			}
		}
		if (game->env.number_npc_meals && \
				(game->env.fat == game->num_npcs))
		{
			ft_endgame(game);
			return (NULL);
		}
		usleep(10);
	}
	return (NULL);
}

static int	ft_check_death(t_npc *philo)
{
	long long	hungry;

	pthread_mutex_lock(&philo->env->m_readwrite);
	hungry = ft_timestamp(philo->t_last_meal);
	if (hungry > philo->env->time_to_die)
	{
		pthread_mutex_unlock(&philo->env->m_readwrite);
		return (1);
	}
	pthread_mutex_unlock(&philo->env->m_readwrite);
	return (0);
}

static void	ft_endgame(t_game *game)
{
	pthread_mutex_lock(&game->env.m_readwrite);
	game->env.death = 1;
	pthread_mutex_unlock(&game->env.m_readwrite);
}
