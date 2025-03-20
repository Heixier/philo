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
	uintptr_t	temp;
	
	i = 0;
	dead = 0;
	while (i < data -> num_philos)
	{
		pthread_mutex_lock(&data -> data);
		temp = p_get_time_ms() - data -> philos[i] -> last_eat_ms;
		pthread_mutex_unlock(&data -> data);
		// if ((p_get_time_ms() - data -> philos[i] -> last_eat_ms > \
		// (uintptr_t)(data -> time_to_die_ms)))
		if (temp > (uintptr_t)(data -> time_to_die_ms))
		{
			pthread_mutex_lock(&data -> data);
			data -> stop_flag = 1;
			pthread_mutex_unlock(&data -> data);
			dead = 1;
			break ;
		}
		i++;
	}

	if (dead)
	{
		pthread_mutex_lock(&data -> print);
		printf("philo %d died at %ld due to %ld elapsed\n", i, p_get_time_ms(), temp);
		printf("%d %d died\n", p_get_timestamp(data -> start_time_ms), i);
		return (pthread_mutex_unlock(&data -> print), 1);
	}
	return (0);
}

void	*p_monitoring_thread(void *data_struct)
{
	t_data	*data;

	data = (t_data *)data_struct;
	p_tick_sleep(data -> time_to_die_ms);
	while (1)
	{
		if (p_report_if_any_are_dead(data))
			return (NULL);
		if (data -> eat_limit_flag && p_hit_eat_limit(data))
			return (p_stop_program(data), NULL);
	}
	return (NULL);	
}

int	p_hit_eat_limit(t_data *data)
{
	int	i;
	int	full_philos;

	i = 0;
	full_philos = 0;
	pthread_mutex_lock(&data -> data);
	while (i < data -> num_philos)
	{
		if (data -> philos[i] -> times_eaten >= data -> eat_limit)
			full_philos++;
		i++;
	}
	if (full_philos == data -> num_philos)
		return (pthread_mutex_unlock(&data -> data), 1);
	pthread_mutex_unlock(&data -> data);
	return (0);
}