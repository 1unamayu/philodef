/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   report.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 18:19:40 by xamayuel          #+#    #+#             */
/*   Updated: 2024/01/28 19:04:03 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void ft_report_screen(int print_type, t_person *person)
{
    unsigned int timestamp;

pthread_mutex_lock(person->data->screen);
timestamp= ft_current_time() - person->data->start_timestamp;
if (print_type == 0)
    printf("%-8.6u\t%d has taken a fork\n", timestamp, person->position+1);
if (print_type == 1)
    printf("%-8.6u\t%d is eating\n", timestamp, person->position+1);
if (print_type == 2)
    printf("%-8.6u\t%d is sleeping\n", timestamp, person->position+1);
if (print_type == 3)
    printf("%-8.6u\t%d is thinking\n", timestamp, person->position+1);
if (print_type == 4)
    printf("%-8.6u\t%d died\n", timestamp, person->position+1);
if (print_type == 5)
    printf("Game over");
if (print_type <4)
    printf("");
    pthread_mutex_unlock(person->data->screen);
}