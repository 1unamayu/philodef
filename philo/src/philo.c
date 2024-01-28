/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 10:52:04 by xamayuel          #+#    #+#             */
/*   Updated: 2024/01/28 20:25:29 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
/**
 * REFERENCES:
 * https://www.um.es/earlyadopters/actividades/a3/PCD_Activity3_Session1.pdf
 * http://profesores.elo.utfsm.cl/~agv/elo330/\
 * 				  2s06/lectures/POSIX_threads/POSIX_Threads_Synchronization.html
 * https://www.thegeekstuff.com/2012/05/c-mutex-examples/
 * 
 * https://www.notion.so/philosophers-VM-c60be9c836084edfbcd9c07e29b429c4
 * 
 * https://hpc-tutorials.llnl.gov/posix/
 * 
 * http://cortesfernando.blogspot.com/2011/12/concurrencia-mutex.html
 * 
 *
 */

int ft_read_game_data(int argn, char **argv, t_game_data *data)
{
	data->num_persons= ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_eating = ft_atoi(argv[3]);
	data->time_sleeping = ft_atoi(argv[4]);
	data->meals_max=-1;
	if (argn == 6)
		data->meals_max = ft_atoi(argv[5]);
	data->endgame = FALSE;
	return (0);
}

t_person *ft_persons_create(t_game_data *data)
{
	t_person *persons;
	int cont;

	cont = 0;
	
	data->screen = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->screen,NULL);
	persons = malloc(sizeof(t_person)*data->num_persons);
	data->thread_person=malloc(sizeof(pthread_t)*data->num_persons); //quitar este 200
	while (cont < data->num_persons)
	{
		//printf("inicializando persona %d \n",cont+1);
		(persons+cont)->position = cont;
		(persons+cont)->lfork = cont;
		(persons+cont)->rfork = ((cont +1) % data->num_persons);
		(persons+cont)->is_death= 0;
		(persons+cont)->data = data;
		(persons+cont)->eating = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init((persons+cont)->eating,NULL);
		//printf("Position            :%d\n", (persons+cont)->position);
		//printf("Left fork position  :%d\n", persons->lfork);
		//printf("Right fork position :%d\n", persons->rfork);
		//printf("Time to eat         :%d\n", persons->data->time_to_die);
		//printf("Numero persons      :%d\n", data->num_persons);
		//printf(" Modulo :%d \n", (1 % 2));
		cont++;
	}
	return (persons);
}

void ft_delete_all(t_person *persons)
{
	free(persons);
}
void ft_delete_game(t_game_data *data)
{
	free(data->forks);
	free(data->thread_person);
}

void ft_take_forks(t_person *person)
{
	//printf("izq: %d\n", person->lfork);
	pthread_mutex_lock(&person->data->forks[person->lfork]);
	ft_report_screen(0,person);
	//printf("dcha: %d\n", person->rfork);
	pthread_mutex_lock(&person->data->forks[person->rfork]);
	ft_report_screen(0,person);
}

void ft_eat(t_person *person)
{
	pthread_mutex_lock(person->eating);
	ft_report_screen(1, person);
	person->num_meals++;
	person->next_meal_timestamp = ft_current_time()+person->data->time_to_die;
	usleep(person->data->time_eating * 1000);
	
	pthread_mutex_unlock(&person->data->forks[person->lfork]);
	pthread_mutex_unlock(&person->data->forks[person->rfork]);
	pthread_mutex_unlock(person->eating);
}

void ft_sleep(t_person *person)
{
	usleep(10);
	ft_report_screen(2,person);
	usleep(person->data->time_sleeping * 1000);
}
void *ft_vida(void *arg)
{
	t_person *person;

	person = arg;
	
	person->next_meal_timestamp = ft_current_time()+person->data->time_to_die;
	

	while (1)
	{
		
		ft_take_forks(person);
		
		ft_eat(person);

		ft_sleep(person);
		
		ft_report_screen(3, person);
		
		
	}
	
	return NULL;
}

void ft_init_game_data(t_game_data *data)
{
	int cont;

	cont = 0;
	
	data->forks = malloc(sizeof(pthread_mutex_t)*data->num_persons);
	while (cont < data->num_persons)
	{
		pthread_mutex_init(data->forks, NULL);
		cont++;
	}
	data->screen=malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->screen,NULL);
	//printf("Jugadores %d\n",data->num_persons);

	
}
int	main(int argn, char *argv[])
{
	t_game_data game_data;
	t_person	*persons;

	pthread_t  huu;
	int cont;

	cont = 0;

	if (argn < 5 || argn > 6)
		return (ft_report_error(ERR_N_ARGS));
	if (!check_all_numeric(argn, argv))
		return (ft_report_error(ERR_NO_NUMBERS));
	
	game_data.num_persons = 0;
	ft_read_game_data(argn, argv, &game_data);
	
	persons = ft_persons_create(&game_data);
	game_data.start_timestamp = ft_current_time();
	ft_init_game_data(&game_data);
	
	cont = 0;
	game_data.thread_person = malloc(sizeof(pthread_t)*game_data.num_persons);
	while (cont < game_data.num_persons)
	{
		//printf("vida %d \n", cont);
		//pthread_create(game_data.thread_person+cont, NULL, ft_vida, persons+cont);
		pthread_create(game_data.thread_person+cont, NULL, ft_vida, persons+cont);
		pthread_detach(game_data.thread_person[cont]);
		//pthread_detach(game_data.thread_person+cont);
		cont ++;
		usleep(100);
		
	}
	while(1) {
        // Hacer otras tareas en el programa principal
        // En este caso, simplemente mantenemos el programa principal en un bucle infinito
    }
	
	ft_delete_all(persons);
	ft_delete_game(&game_data);
	//system("valgrind --leak-check=full ./philo");
	return (0);
}
