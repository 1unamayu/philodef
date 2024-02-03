/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_life.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:21:55 by xamayuel          #+#    #+#             */
/*   Updated: 2024/02/04 00:00:18 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_npc_eats(t_npc *npc);

void	*ft_npc_life(void *args)
{
	t_npc	*npc;

	npc = (t_npc *) args;
	if (!(npc->id_npc % 2))
		usleep(15000);
	pthread_mutex_lock(&npc->env->m_main);
	pthread_mutex_unlock(&npc->env->m_main);
	while (!ft_check_changes_philo(npc))
	{
		if (!ft_npc_eats(npc))
		{
			if (npc->env->number_npc_meals == npc->meals_eaten)
			{
				npc->env->number_full++;
				return (NULL);
			}
		}
		else
			return (NULL);
		ft_print(npc, "is sleeping");
		ft_usleep(npc->env->time_sleeping);
		ft_print(npc, "is thinking");
	}
	return (NULL);
}

static int	ft_npc_eats(t_npc *npc)
{
	if (pthread_mutex_lock(&npc->m_npc_death))
		return (1);
	pthread_mutex_unlock(&npc->m_npc_death);
	pthread_mutex_lock(npc->m_lfork);
	ft_print(npc, "has taken a fork");
	if (npc->m_rfork)
		pthread_mutex_lock(npc->m_rfork);
	else
		return (1);
	ft_print(npc, "has taken a fork");
	ft_print(npc, "is eating");
	npc->meals_eaten++;
	pthread_mutex_lock(&npc->env->m_readwrite);
	npc->t_last_meal = ft_current_time();
	pthread_mutex_unlock(&npc->env->m_readwrite);
	ft_usleep(npc->env->time_eating);
	pthread_mutex_unlock(npc->m_lfork);
	pthread_mutex_unlock(npc->m_rfork);
	return (0);
}

int	ft_check_changes_philo(t_npc *npc)
{
	pthread_mutex_lock(&npc->env->m_readwrite);
	if (npc->env->death)
	{
		pthread_mutex_unlock(&npc->env->m_readwrite);
		return (1);
	}
	pthread_mutex_unlock(&npc->env->m_readwrite);
	return (0);
}
