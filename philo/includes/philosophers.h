/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:20:46 by xamayuel          #+#    #+#             */
/*   Updated: 2024/02/07 19:45:21 by xamayuel         ###   ########.fr       */
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

# define ERR_N_ARGS 100
# define ERR_NO_NUMBERS 200
# define ERR_ZERO 300
# define ERR_MALLOC 10
# define ERR_MUTEX 20
# define ERR_MINIMUM 15
# define ERR_NONUMERIC 600
# define FALSE 0
# define TRUE 1

# define FORK 0
# define EATING 1
# define DIED 2
# define FORKK 100
# define SLEEP 3
# define THINK 5

typedef struct s_data
{
	int				time_to_die;
	int				time_eating;
	int				time_sleeping;
	int				number_npc_meals;
	long long		t_start;			// Start timestamp
	int				death;				// Someone is death
	int				number_full;		// Npcs that has eaten min meals
	pthread_mutex_t	m_screen; //Mutex to protec stdout
	pthread_mutex_t	m_main; //Mutex to protect threads
	pthread_mutex_t	m_readwrite; //Mutex to protec read write data race
}			t_data;

typedef struct s_npc
{
	int				id_npc; // NPC ID (POSITION)
	pthread_t		id_thread; // NPC THREAD
	int				meals_eaten; //Number of NPC has eat
	long long		t_last_meal; //Timestampo of the last npc meal
	pthread_mutex_t	m_npc_death; //MUtex to proctec death
	pthread_mutex_t	*m_lfork; //mutex to protect npc left fork
	pthread_mutex_t	*m_rfork; //Mutex to protec npc right fork
	t_data			*env;
}			t_npc;

typedef struct s_game
{
	int				num_npcs;	// Number of NPCs players
	pthread_t		doctor;		// Thread to control npcs health
	pthread_mutex_t	*forks;		// Mutex to protect forks
	t_npc			*npcs;
	t_data			env;
}			t_game;

// errors_show
void		ft_report_error(int type);
// ft_atoi
int			ft_atoi(const char *str);
//game_data_checks
int			ft_valid_input(int argn, char **argv);
//game_data
void		ft_set_game(char **data, int argc, t_game *game);
//game_free
void		ft_free_game(t_game *game);
//game_start
int			ft_start_game(t_game *game);
//npc_doctor
void		*ft_doctor_health(void *args);
//npc_life
void		*ft_npc_life(void *args);
int			ft_check_death_philo(t_npc *philo);
//npc_print
void		ft_print(t_npc *philo, char *msg);
//timestamps
void		ft_usleep(long long time);
long long	ft_timestamp(long long time);
long long	ft_current_time(void);

#endif