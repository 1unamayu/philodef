/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 10:52:04 by xamayuel          #+#    #+#             */
/*   Updated: 2024/01/28 11:59:31 by xamayuel         ###   ########.fr       */
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
	persons = malloc(sizeof(t_person)*10);
	return (persons);
}

int	main(int argn, char *argv[])
{
	t_game_data game_data;
	t_person	*person;

	if (argn < 5 || argn > 6)
		return (ft_report_error(ERR_N_ARGS));
	if (!check_all_numeric(argn, argv))
		return (ft_report_error(ERR_NO_NUMBERS));
	
	game_data.num_persons = 0;
	printf("%d\n",game_data.num_persons);

	ft_read_game_data(argn, argv, &game_data);
	
	person = ft_persons_create(&game_data);

	//init_game(&npcs, argn, argv);
	//start_game(npcs);

	
	return (0);
}
