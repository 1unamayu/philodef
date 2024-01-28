/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:30:02 by xamayuel          #+#    #+#             */
/*   Updated: 2024/01/29 00:32:50 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void ft_create_mutex(t_game *game)
{
	int j;

	pthread_mutex_init(&game->env.message, NULL);
	pthread_mutex_init(&game->env.control, NULL);
	pthread_mutex_init(&game->env.death_in_table, NULL);

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

	person->lfork = &game->forks[(person->pid -1)];
	position = (person->pid ) % game->total_persons;
	//printf("Left %d\n", person->pid -1);
	//printf("Right %d\n", position);
	person->rfork = &game->forks[position];
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
int ft_is_death(t_person *person)
{

	pthread_mutex_lock(&person->env->death_in_table);
	if (ft_current_time() > person->last_meal_timestamp)
	{
		pthread_mutex_unlock(&person->env->death_in_table);
		return (TRUE);
	}
	pthread_mutex_unlock(&person->env->death_in_table);
	return (FALSE);
}

void ft_endgame(t_game *game)
{
	pthread_mutex_lock(&game->env.death_in_table);
	game->env.death=1;
	pthread_mutex_unlock(&game->env.death_in_table);
}
void ft_report(t_person *person, int type)
{
	long long timestamp;
	
	timestamp = ft_current_time()-person->env->start_timestamp;
	if (type == FORK)
		printf("%.04lld   %d has taken a fork",timestamp, person->pid);
	if (type == EATING)
		printf("%.04lld   %d is eating",timestamp, person->pid);
	if (type == DIED)
		printf("%.04lld   %d died",timestamp, person->pid);
}
void *ft_doctor(void *args)
{
	t_game	*allgame;
	int j;

	allgame =(t_game *)args;
	while(allgame->env.death ==0)
	{
		j=-1;
		while(++j < allgame->total_persons)
		{
			if (ft_is_death(&allgame->persons[j]))
			{
				ft_report(&allgame->persons[j], DIED);
				ft_endgame(allgame);
				return (NULL);
			}
		}

	}
	return (NULL);
}

int check_game_end(t_game *game)
{
	pthread_mutex_lock(&game->env.death_in_table);
	if (game->env.death)
	{
		pthread_mutex_unlock(&game->env.death_in_table);
		return(TRUE);
	}

	pthread_mutex_unlock(&game->env.death_in_table);
	return (FALSE);
}

int check_person(t_person *person)
{
	pthread_mutex_lock(&person->env->death_in_table);
	if (person->env->death)
	{
		pthread_mutex_unlock(&person->env->death_in_table);
		return(TRUE);
	}

	pthread_mutex_unlock(&person->env->death_in_table);
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
	printf("dentor de eats\n");
	//if (pthread_mutex_lock(&person->death))
	//	return (1);
	pthread_mutex_unlock(&person->death);
	pthread_mutex_lock(person->lfork);
	ft_report(person, 0);
	pthread_mutex_lock(person->lfork);
	ft_report(person, FORK);
	ft_report(person, EATING);
	person->meals++;
	pthread_mutex_lock(&person->env->death_in_table);
	ft_sleep(person->env->time_eat);
	pthread_mutex_unlock(person->lfork);
	pthread_mutex_unlock(person->rfork);
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
	printf("life %d\n",check_person(person));

	while(check_person(person)== FALSE)
	{
		if (!ft_person_eats(person))
		{
			person->env->n_meals++;
		}
		else
			return (NULL);
	}
}
void ft_create_threads(t_game *game)
{
	int j;

	j= -1;
	printf("Dentro de create threads\n");
	pthread_mutex_lock(&game->env.control);
	if (pthread_create(&game->doctor, NULL, &ft_doctor,game))
		report_error(ERR_MALLOC);
	
	while (++j < game->total_persons)
	{
		printf("PERSON %d\n", j);
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