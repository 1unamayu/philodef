/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:27:01 by xamayuel          #+#    #+#             */
/*   Updated: 2024/02/04 13:45:17 by xamayuel         ###   ########.fr       */
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

/**
 * @brief Sleeps for a specified duration.
 * 
 * This function sleeps for a specified duration in milliseconds. It starts 
 * measuring time from the current time and continues sleeping until the 
 * specified duration has elapsed. It uses a busy-wait loop with short 
 * usleep intervals for precise timing.
 * 
 * @param time The duration to sleep in milliseconds.
 */
void	ft_usleep(long long time)
{
	long long	start;

	start = ft_current_time();
	while ((ft_current_time() - start) < time)
		usleep(300);
}

/**
 * @brief Calculates the time difference between two timestamps.
 * 
 * This function calculates the time difference between the current time 
 * and a given timestamp. It returns the difference in milliseconds.
 * 
 * @param time The timestamp to calculate the difference from.
 * @return Returns the time difference in milliseconds.
 */
long long	ft_timestamp(long long time)
{
	long long		now;

	now = ft_current_time();
	return (now - time);
}
