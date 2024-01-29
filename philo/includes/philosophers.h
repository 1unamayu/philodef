/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:20:46 by xamayuel          #+#    #+#             */
/*   Updated: 2024/01/29 09:44:10 by xamayuel         ###   ########.fr       */
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

# define FORK 0
# define EATING 1
# define DIED 2
# define FORKK 100
# define SLEEP 3
# define THINK 5

typedef struct s_env
{
	int 	time_die;
	int 	time_eat;
	int		time_sleep;
	int 	max_meals;
	long long	start_timestamp;
	int 	death;
	int 	n_meals;
	pthread_mutex_t message;
	pthread_mutex_t control;
	pthread_mutex_t m_readwrite; /*Mutex to avoid dataraces in read write*/
} t_env;

typedef struct s_person
{
	int 	pid;
	pthread_t 	tid;
	int meals;
	long long last_meal_timestamp;
	pthread_mutex_t death;
	pthread_mutex_t *m_lfork;
	pthread_mutex_t *m_rfork;
	t_env	*env;
} t_person;

typedef struct s_game
{
	int total_persons;
	pthread_t doctor;
	pthread_mutex_t *forks;
	t_person	*persons;
	t_env env;
}t_game;

int	check_all_numeric(int argn, char *argv[]);
void	report_error(int type);
void	show_error_arguments(void);
int	ft_error(char *string);
int	ft_atoi(const char *str);
long long	ft_current_time(void);
void ft_free_game(t_game *game);
void ft_start_game(t_game *game);

void ft_report(t_person *person, int type);
void    *ft_doctor(void *args);
#endif