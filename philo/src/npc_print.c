/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:30:10 by xamayuel          #+#    #+#             */
/*   Updated: 2024/02/07 19:45:29 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Functions for printing messages related to philosopher actions.
 * 
 * This file contains functions for printing messages related to philosopher 
 * actions in the philosophers game. It includes a function for printing 
 * messages indicating the state of a philosopher, such as eating, sleeping, 
 * or thinking.
 */

#include <philosophers.h>

/**
 * @brief Prints a message indicating the state of a philosopher.
 * 
 * This function prints a message indicating the current state of a philosopher, 
 * such as eating, sleeping, or thinking. It locks the screen mutex to ensure 
 * thread safety during printing. It checks for changes in the philosopher's 
 * environment to determine if the message should be printed. It prints the 
 * message along with the philosopher's ID and the current time elapsed since 
 * the start of the game.
 * 
 * @param npc Pointer to the philosopher structure.
 * @param msg Pointer to the message to be printed.
 */
void	ft_print(t_npc *npc, char *msg)
{
	long long	now;

	pthread_mutex_lock(&npc->env->m_screen);
	now = ft_current_time() - npc->env->t_start;
	if (!ft_check_death_philo(npc))
		printf("%-8.6lld  %d %s\n", now, npc->id_npc, msg);
	pthread_mutex_unlock(&npc->env->m_screen);
}
