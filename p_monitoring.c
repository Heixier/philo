/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_monitoring.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:06:57 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/19 20:50:52 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Checks if too much time has elapsed since it last ate (lock before using)
int	p_is_dead(t_philo *philo)
{
	int			dead;
	uintptr_t	diff;

	diff = (p_get_time_ms() - philo -> last_eat_ms);
	
	if (diff > (uintptr_t)(philo -> data -> time_to_eat_ms))
		dead = 1;
	else
		dead = 0;
	return (dead);
}

// Will lock data and print in case any dies, returns 1 if dead
int	p_report_if_any_are_dead(t_data *data)
{
	int	i;
	
	i = 0;
	pthread_mutex_lock(&data -> data);
	while (i < data -> num_philos)
	{
		if (p_is_dead(data -> philos[i]))
		{
			pthread_mutex_lock(&data -> print);
			printf("%d %d died\n", p_get_timestamp(data -> start_time_ms), i);
			pthread_mutex_unlock(&data -> print);
			return (pthread_mutex_unlock(&data -> data), 1);
		}
		i++;
	}
	pthread_mutex_unlock(&data -> data);
	return (0);
}

void	*p_monitoring_thread(void *data_struct)
{
	t_data	*data;

	data = (t_data *)data_struct;
	while (1)
	{
		if (p_check_if_stopped(data))
			return (NULL);
		if (p_report_if_any_are_dead(data))
			return (p_stop_program(data), NULL);
	}
	return (NULL);	
}
