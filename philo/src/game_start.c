/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 23:56:17 by xamayuel          #+#    #+#             */
/*   Updated: 2024/02/04 13:47:35 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Function for starting and managing the execution of the game.
 * 
 * This file contains a function for starting and managing the execution of the 
 * philosophers game. It includes a function for waiting for the completion of 
 * philosopher threads and the doctor thread, ensuring that all threads have 
 * completed their execution.
 * 
 */

#include <philosophers.h>

/**
 * @brief Starts and manages the execution of the game.
 * 
 * This function starts and manages the execution of the philosophers game. 
 * It waits for the completion of philosopher threads and the doctor thread, 
 * ensuring that all threads have completed their execution before returning.
 * 
 * @param game Pointer to the game structure.
 * @return Returns 0 upon successful completion of all threads.
 */
int	ft_start_game(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->num_npcs)
	{
		if (pthread_join(game->npcs[i].id_thread, NULL))
			ft_report_error(ERR_MALLOC);
	}
	if (pthread_join(game->doctor, NULL))
		ft_report_error(ERR_MALLOC);
	return (0);
}
