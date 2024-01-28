/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 10:27:22 by xamayuel          #+#    #+#             */
/*   Updated: 2024/01/28 10:45:13 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

# define RED "\033[0;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[0;33m"
# define PURPLE "\033[0;35m"
# define CYAN "\x1b[36m"
# define WHITE "\033[0;37m"
# define BLACK "\033[1;30m"

# define ERR_N_ARGS 1
# define ERR_NO_NUMBERS 2
# define ERR_ZERO 3
# define ERR_MALLOC 4
# define ERR_MUTEX 5
# define FALSE 0
# define TRUE 1

typedef struct s_game_data
{
	
	pthread_t 		*persons;
	pthread_mutex_t	*forks;
	pthread_mutex_t	screen;
	pthread_mutex_t	death;
	pthread_mutex_t	endgame;


	


	unsigned int	num_persons;		/**< Number of Philosophers. */
	unsigned int	time_to_die;		/**< Time to die [arg(1)]. */
	unsigned int	time_eating;		/**< Time eating [arg(2)]. */
	unsigned int	time_sleeping;		/**< Time sleeping [arg(3)]. */
	unsigned int	meals_max;			/**< Min. numb of meals each philosopher[arg(4)]. */
	unsigned int	endgame;
	
	
}	t_game_data;

typedef struct s_persons
{
	unsigned int		position;
	unsigned int		num_meals;
	long long int		last_meal_timestamp;
	long long int		start_timestamp;
	
	t_game_data			*data;
	
}	t_person;


#endif