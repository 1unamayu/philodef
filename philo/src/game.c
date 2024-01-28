/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 23:56:17 by xamayuel          #+#    #+#             */
/*   Updated: 2024/01/28 23:57:20 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void ft_start_game(t_game *game)
{
	int j;

	j=-1;
	while (++j < game->total_persons)
	{
		if(pthread_join(game->persons[j].tid,NULL))
			report_error(ERR_MUTEX);
	}
	if(pthread_join(game->doctor,NULL))
		report_error(ERR_MUTEX);
}