/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doctor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:10:08 by xamayuel          #+#    #+#             */
/*   Updated: 2024/01/29 09:19:32 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static void ft_endgame(t_game *game);
static int ft_is_death(t_person *person);

void    *ft_doctor(void *args)
{
	t_game	*allgame;
	int j;

	allgame =(t_game *)args;
	while(allgame->env.death ==0)
	{
		j=-1;
		while(++j < allgame->total_persons)
		{
			//printf("Dentro de doctor %lld\n", ft_current_time());
			if (ft_is_death(&allgame->persons[j]))
			{
				ft_report(&allgame->persons[j], DIED);
				ft_endgame(allgame);
				return (NULL);
			}
		}
		if (allgame->env.n_meals > 0 && allgame->env.n_meals == allgame->total_persons)
		{
			ft_endgame(allgame);
			return (NULL);
		}
		usleep(10);
	}
	return (NULL);
}
static int ft_is_death(t_person *person)
{

	pthread_mutex_lock(&person->env->m_readwrite);
	//printf("dentro de death current %lld lastmeall %lld\n", ft_current_time(), person->last_meal_timestamp);
	//printf("time to die %d\n", person->env->time_die);
	if (ft_current_time() > person->last_meal_timestamp + person->env->time_die)
	{
		pthread_mutex_unlock(&person->env->m_readwrite);
		return (TRUE);
	}
	pthread_mutex_unlock(&person->env->m_readwrite);
	return (FALSE);
}

static void ft_endgame(t_game *game)
{
	pthread_mutex_lock(&game->env.m_readwrite);
	game->env.death=1;
	pthread_mutex_unlock(&game->env.m_readwrite);
}