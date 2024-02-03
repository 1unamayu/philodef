/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_life.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:21:55 by xamayuel          #+#    #+#             */
/*   Updated: 2024/02/03 23:12:34 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_npc_eats(t_npc *philo);

void	*ft_npc_life(void *args)
{
	t_npc	*philo;

	philo = (t_npc *) args;
	if (!(philo->id_npc % 2))
		usleep(15000);
	pthread_mutex_lock(&philo->env->m_main);
	pthread_mutex_unlock(&philo->env->m_main);
	while (!ft_check_changes_philo(philo))
	{
		if (!ft_npc_eats(philo))
		{
			if (philo->env->number_npc_meals == philo->meals_eaten)
			{
				philo->env->fat++;
				return (NULL);
			}
		}
		else
			return (NULL);
		ft_print(philo, "is sleeping");
		ft_usleep(philo->env->time_sleeping);
		ft_print(philo, "is thinking");
	}
	return (NULL);
}

static int	ft_npc_eats(t_npc *philo)
{
	if (pthread_mutex_lock(&philo->m_npc_death))
		return (1);
	pthread_mutex_unlock(&philo->m_npc_death);
	pthread_mutex_lock(philo->m_lfork);
	ft_print(philo, "has taken a fork");
	if (philo->m_rfork)
		pthread_mutex_lock(philo->m_rfork);
	else
		return (1);
	ft_print(philo, "has taken a fork");
	ft_print(philo, "is eating");
	philo->meals_eaten++;
	pthread_mutex_lock(&philo->env->m_readwrite);
	philo->t_last_meal = ft_current_time();
	pthread_mutex_unlock(&philo->env->m_readwrite);
	ft_usleep(philo->env->time_eating);
	pthread_mutex_unlock(philo->m_lfork);
	pthread_mutex_unlock(philo->m_rfork);
	return (0);
}

/*
int	ft_npc_dies(t_npc *philo)
{
	if (philo->env->death)
		return (1);
	ft_print(philo, "died");
	philo->env->death = 1;
	pthread_mutex_lock(&philo->m_npc_death);
	return (0);
}
// falta check changes table????*/
int	ft_check_changes_philo(t_npc *philo)
{
	pthread_mutex_lock(&philo->env->m_readwrite);
	if (philo->env->death)
	{
		pthread_mutex_unlock(&philo->env->m_readwrite);
		return (1);
	}
	pthread_mutex_unlock(&philo->env->m_readwrite);
	return (0);
}
