/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 10:52:04 by xamayuel          #+#    #+#             */
/*   Updated: 2024/01/28 11:11:08 by xamayuel         ###   ########.fr       */
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

int	main(int argn, char *argv[])
{
	//t_npc	*npcs;

	if (argn < 5 || argn > 6)
		return (ft_report_error(ERR_N_ARGS));
	if (!check_all_numeric(argn, argv))
		return (ft_report_error(ERR_NO_NUMBERS));
	
	//init_game(&npcs, argn, argv);
	//start_game(npcs);
	return (0);
}
