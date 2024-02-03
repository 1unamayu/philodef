/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:27:01 by xamayuel          #+#    #+#             */
/*   Updated: 2024/02/04 00:00:29 by xamayuel         ###   ########.fr       */
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

void	ft_usleep(long long time)
{
	long long	start;

	start = ft_current_time();
	while ((ft_current_time() - start) < time)
		usleep(300);
}

long long	ft_timestamp(long long time)
{
	long long		now;

	now = ft_current_time();
	return (now - time);
}
