/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 23:18:17 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/28 03:23:31 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	 main(int argc, char **argv)
{
	t_data	*data;

	data = p_init_philo_data(argc, argv);
	if (!data)
		return (1);
	p_print_debug(data);
	p_start_philosopher_threads(data);
	p_cleanup(data);
	return (0);
}

void	p_print_debug(t_data *data)
{
	printf("Data:\n\nNumber of philosophers: %d\nStart time ms: %ld\n\
Time to die ms: %d\nTime to eat ms: %d\nTime to sleep ms: %d\nEat limit flag: %d\n\
Eat limit: %d\n", data -> num_philos, data -> start_time_ms, data -> time_to_die_ms, \
data -> time_to_eat_ms, data -> time_to_sleep_ms, data -> eat_limit_flag, data -> eat_limit);
	// while (i < data -> num_philos)
	// {
	// 	printf("\nPhilosopher id %d:\n\nTimes eaten: %d\nTime_since_eaten: %ld\n", 
	// 	data -> philos[i] -> id, data -> philos[i] -> times_eaten, data -> philos[i] -> last_eat_ms);
	// 	i++;
	// }
}

void	p_print_debug_individual(t_philo *philo)
{
	pthread_mutex_lock(&philo -> data -> print_mutex);
	printf("Start time: %ld\n", philo -> data -> start_time_ms);
	printf("\nPhilosopher id %d:\n\nTimes eaten: %d\nLast ate at: %ld\nCurrent tim: %ld\nElapsed: %ld\n", \
	philo -> id, philo -> times_eaten, philo -> last_eat_ms, p_get_time_ms(), p_get_time_ms() - philo -> last_eat_ms);
	pthread_mutex_unlock(&philo -> data -> print_mutex);
}
