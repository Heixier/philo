/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_monitoring.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:06:57 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/20 21:49:45 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Will lock data and print in case any dies, returns 1 if dead
int	p_report_if_any_are_dead(t_data *data)
{
	int	i;
	int	dead;
	uintptr_t	time_elapsed;
	uintptr_t	time;
	
	i = 0;
	dead = 0;
	while (i < data -> num_philos)
	{
		// p_print_debug_individual(data -> philos[i]);
		time = p_get_time_ms();
		pthread_mutex_lock(&data -> philos[i] -> eat);
		time_elapsed = time - data -> philos[i] -> last_eat_ms;
		pthread_mutex_unlock(&data -> philos[i] -> eat);
		// if (time_elapsed > (uintptr_t)(data->time_to_die_ms - 50)) {  // Warning when getting close
		// 	pthread_mutex_lock(&data->print);
		// 	printf("WARNING: Philo %d - %lu ms since last meal (limit: %d)\n", 
		// 		   i, time_elapsed, data->time_to_die_ms);
		// 	pthread_mutex_unlock(&data->print);
		// }
		if (time_elapsed > (uintptr_t)(data -> time_to_die_ms))
		{
			p_stop_program(data);
			dead = 1;
			break ;
		}
		i++;
	}
	if (dead)
	{
		pthread_mutex_lock(&data -> print);
		// printf("philo %d died at %ld due to %ld elapsed\n", i, p_get_time_ms(), temp);
		printf("%d %d died\n", p_get_timestamp(data -> start_time_ms), i);
		return (pthread_mutex_unlock(&data -> print), 1);
	}
	return (0);
}

void	*p_monitoring_thread(void *data_struct)
{
	t_data	*data;

	data = (t_data *)data_struct;
	p_tick_sleep(10);
	while (1)
	{
		if (p_report_if_any_are_dead(data))
			return (NULL);
		if (data -> eat_limit_flag && p_hit_eat_limit(data))
			return (p_stop_program(data), NULL);
		usleep(1000);
	}
	return (NULL);	
}

int	p_hit_eat_limit(t_data *data)
{
	int	i;
	int	full_philos;

	i = 0;
	full_philos = 0;
	while (i < data -> num_philos)
	{
		pthread_mutex_lock(&data -> philos[i] -> eat);
		if (data -> philos[i] -> times_eaten >= data -> eat_limit)
			full_philos++;
		pthread_mutex_unlock(&data -> philos[i] -> eat);
		i++;
	}
	if (full_philos == data -> num_philos)
		return (1);
	return (0);
}
