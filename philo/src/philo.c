/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:30:02 by xamayuel          #+#    #+#             */
/*   Updated: 2024/01/29 09:54:45 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void ft_create_mutex(t_game *game)
{
	int j;

	pthread_mutex_init(&game->env.message, NULL);
	pthread_mutex_init(&game->env.control, NULL);
	pthread_mutex_init(&game->env.m_readwrite, NULL);

	game->forks = malloc(sizeof(pthread_mutex_t)*game->total_persons);
	if (!game->forks)
		report_error(ERR_MALLOC);
	j=-1;
	while (++j>game->total_persons)
	{
		if (pthread_mutex_init(&game->forks[j],NULL))
		report_error(ERR_MALLOC);
	}
}

void ft_create_forks(t_person *person, t_game *game)
{
	int position;

	person->m_lfork = &game->forks[(person->pid -1)];
	if (person->pid == game->total_persons)
		person->m_rfork= &game->forks[0];
	else
		person->m_rfork= &game->forks[person->pid];
	if (game->total_persons == 1)
		person->m_rfork = NULL;
}

void ft_create_philos(t_game *game)
{
	int j;

	game->persons= malloc(sizeof(t_person)*game->total_persons);
	if(!game->persons)
		report_error(ERR_MALLOC);
	j= -1;
	while (++j < game->total_persons)
	{
		game->persons[j].pid= j+1;
		game->persons[j].meals = 0;
		game->persons[j].last_meal_timestamp= game->env.start_timestamp;
		game->persons[j].env = &game->env;
		ft_create_forks(&game->persons[j],game);
		pthread_mutex_init(&game->persons[j].death, NULL);
		
	}
}

void ft_report(t_person *person, int type)
{
	long long timestamp;
	
	timestamp = ft_current_time()-person->env->start_timestamp;
	if (type == FORK)
		printf("%.04lld   %d has taken a fork\n",timestamp, person->pid);
	if (type == FORKK)
		printf("%.04lld   %d has taken a rfork\n",timestamp, person->pid);
	if (type == EATING)
		printf("%.04lld   %d is eating\n",timestamp, person->pid);
	if (type == DIED)
		printf("%.04lld   %d died\n",timestamp, person->pid);
	if (type == SLEEP)
		printf("%.04lld   %d is sleeping\n",timestamp, person->pid);
	if (type == THINK)
		printf("%.04lld   %d is thinking\n",timestamp, person->pid);
}


int check_game_end(t_game *game)
{
	pthread_mutex_lock(&game->env.m_readwrite);
	if (game->env.death)
	{
		pthread_mutex_unlock(&game->env.m_readwrite);
		return(TRUE);
	}

	pthread_mutex_unlock(&game->env.m_readwrite);
	return (FALSE);
}

int check_person(t_person *person)
{
	pthread_mutex_lock(&person->env->m_readwrite);
	if (person->env->death)
	{
		pthread_mutex_unlock(&person->env->m_readwrite);
		return(TRUE);
	}

	pthread_mutex_unlock(&person->env->m_readwrite);
	return (FALSE);
}


void ft_sleep(long long time)
{
	long long start;

	start = ft_current_time();
	while ((ft_current_time()-start)<time)
		usleep(300);
}
int ft_person_eats(t_person *person)
{
	//printf("dentor de eats\n");
	//if (pthread_mutex_lock(&person->death))
	//	return (1);
	pthread_mutex_unlock(&person->death);
	pthread_mutex_lock(person->m_lfork);
	ft_report(person, FORK);
	if (person->m_rfork)
		pthread_mutex_lock(person->m_rfork);
	else
		return (TRUE);
	//printf("segundo fork\n");
	ft_report(person, FORKK);
	ft_report(person, EATING);
	person->meals++;
	pthread_mutex_lock(&person->env->m_readwrite);
	person->last_meal_timestamp = ft_current_time();
	pthread_mutex_unlock(&person->env->m_readwrite);
	printf("a dormir!\n");
	ft_sleep(person->env->time_eat);
	pthread_mutex_unlock(person->m_lfork);
	pthread_mutex_unlock(person->m_rfork);
	return (FALSE);
}
void *ft_life(void *args)
{
	t_person *person;

	//printf("life");
	person = (t_person *)args;
	if (!person->pid %2)
		usleep(15000);
	pthread_mutex_lock(&person->env->control);
	pthread_mutex_unlock(&person->env->control);
	//printf("life %d\n",check_person(person));

	while(check_person(person)== FALSE)
	{
		if (!ft_person_eats(person))
		{
			person->env->n_meals++;
			return (NULL);
		}
		else
			return (NULL);
		ft_report(person, SLEEP);
		ft_sleep(person->env->time_sleep);
		ft_report(person, THINK);
	}
}
void ft_create_threads(t_game *game)
{
	int j;

	j= -1;
	//printf("Dentro de create threads\n");
	pthread_mutex_lock(&game->env.control);
	if (pthread_create(&game->doctor, NULL, &ft_doctor,game))
		report_error(ERR_MALLOC);
	
	while (++j < game->total_persons)
	{
		//printf("PERSON %d\n", j);
		if (pthread_create(&game->persons[j].tid,NULL,&ft_life, &game->persons[j]))
			report_error(ERR_MALLOC);
	}
	pthread_mutex_unlock(&game->env.control);
	
}
void ft_set_game(char *argv[], int argn, t_game *game)
{
	game->total_persons = ft_atoi(argv[1]);
	game->env.death = 0;
	game->env.n_meals = 0;
	game->env.time_die = ft_atoi(argv[2]);
	game->env.time_eat= ft_atoi(argv[3]);
	game->env.time_sleep = ft_atoi(argv[4]);
	game->env.max_meals = 0;
	if (argn == 6)
	game->env.max_meals = ft_atoi(argv[5]);
	ft_create_mutex(game);
	game->env.start_timestamp = ft_current_time();
	ft_create_philos(game);
	ft_create_threads(game);
}


int	main(int argn, char *argv[])
{
	t_game	game;

	if (argn < 5 || argn > 6)
		report_error(ERR_N_ARGS);
	if (check_all_numeric(argn, argv) == FALSE)
		report_error(ERR_NO_NUMBERS);
	ft_set_game(argv,argn, &game);	
	ft_start_game(&game);
	ft_free_game(&game);
	return (0);
}