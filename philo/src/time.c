/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:27:01 by xamayuel          #+#    #+#             */
/*   Updated: 2024/01/28 21:48:22 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Get the current time in milliseconds.
 * 
 * This function retrieves the current time using the gettimeofday function,
 * which provides time in seconds and microseconds. It converts the time
 * to milliseconds and returns the result.
 * 
 * @return Returns the current time in milliseconds.
 */
long long	ft_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
