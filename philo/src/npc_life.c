/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_life.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:21:55 by xamayuel          #+#    #+#             */
/*   Updated: 2024/02/04 13:46:29 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Functions for simulating the life cycle of philosophers in the game.
 * 
 * This file contains functions for simulating the life cycle of philosophers 
 * in the philosophers game. It includes a function for each philosopher thread 
 * that represents the life cycle of a philosopher, including eating, sleeping, 
 * and thinking.
 */

#include "philosophers.h"

static int	ft_npc_eats(t_npc *npc);

/**
 * @brief Simulates the life cycle of a philosopher.
 * 
 * This function simulates the life cycle of a philosopher. It represents a 
 * philosopher thread that continuously performs eating, sleeping, and thinking 
 * actions until certain conditions are met, such as the philosopher has eaten 
 * a certain number of meals or the game ends. It returns NULL upon completion 
 * of the philosopher's life cycle.
 * 
 * @param args Pointer to the philosopher structure.
 * @return Returns NULL upon completion of the philosopher's life cycle.
 */
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

/**
 * @brief Simulates a philosopher eating.
 * 
 * This function simulates a philosopher eating by acquiring two forks, 
 * eating for a certain period, and then releasing the forks. It updates the 
 * philosopher's attributes such as the number of meals eaten and the time of 
 * the last meal. It returns 0 upon successful completion of eating, otherwise 
 * returns 1.
 * 
 * @param npc Pointer to the philosopher structure.
 * @return Returns 0 upon successful completion of eating, otherwise returns 1.
 */
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

/**
 * @brief Checks for changes in the philosopher's environment.
 * 
 * This function checks for changes in the philosopher's environment, such as 
 * the end of the game. It locks the read-write mutex to access the game 
 * environment safely. It returns 1 if there are changes that require the 
 * philosopher to stop its life cycle, otherwise returns 0.
 * 
 * @param npc Pointer to the philosopher structure.
 * @return Returns 1 if there are changes that require the philosopher to 
 * stop its life cycle, otherwise returns 0.
 */
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
