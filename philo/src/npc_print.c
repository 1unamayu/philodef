/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:30:10 by xamayuel          #+#    #+#             */
/*   Updated: 2024/02/03 23:11:27 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	ft_print(t_npc *philo, char *msg)
{
	long long	now;

	pthread_mutex_lock(&philo->env->m_screen);
	now = ft_current_time() - philo->env->t_start;
	if (!ft_check_changes_philo(philo))
		printf("%-8.6lld  %d %s\n", now, philo->id_npc, msg);
	pthread_mutex_unlock(&philo->env->m_screen);
}
