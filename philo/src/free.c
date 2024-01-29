/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 23:39:27 by xamayuel          #+#    #+#             */
/*   Updated: 2024/01/29 09:19:27 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>


void ft_free_game(t_game *game)
{
    int j;

    pthread_mutex_destroy(&game->env.message);
    pthread_mutex_destroy(&game->env.control);
    pthread_mutex_destroy(&game->env.m_readwrite);
    j=-1;
    while (++j < game->total_persons)
    {
        pthread_mutex_destroy(&game->forks[j]);
        pthread_mutex_destroy(&game->persons[j].death);
    }
    free(game->forks);
    free(game->persons);
}