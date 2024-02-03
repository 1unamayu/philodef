/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 23:56:17 by xamayuel          #+#    #+#             */
/*   Updated: 2024/02/03 22:57:07 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	ft_start_game(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->num_npcs)
	{
		if (pthread_join(game->philos[i].id_thread, NULL))
			ft_report_error(ERR_MALLOC);
	}
	if (pthread_join(game->doctor, NULL))
		ft_report_error(ERR_MALLOC);
	return (0);
}
