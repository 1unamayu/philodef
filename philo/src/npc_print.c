/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:30:10 by xamayuel          #+#    #+#             */
/*   Updated: 2024/02/03 23:48:33 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	ft_print(t_npc *npc, char *msg)
{
	long long	now;

	pthread_mutex_lock(&npc->env->m_screen);
	now = ft_current_time() - npc->env->t_start;
	if (!ft_check_changes_philo(npc))
		printf("%-8.6lld  %d %s\n", now, npc->id_npc, msg);
	pthread_mutex_unlock(&npc->env->m_screen);
}
