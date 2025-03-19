/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_monitoring.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:06:57 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/19 14:49:59 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Checks if too much time has elapsed since it last ate
int	p_is_dead(t_philo *philo)
{
	int			dead;
	uintptr_t	diff;

	diff = (p_get_time_ms() - philo -> last_eat_ms);
	
	if (diff > (uintptr_t)(philo -> data -> time_to_eat_ms))
	{
		// temporary prints
		printf("%d %d died\n", \
			p_get_timestamp(philo -> data -> start_time_ms), philo -> id);
		dead = 1;
	}
	else
	{
		printf("%d %d survived (diff: %ld)\n", \
			p_get_timestamp(philo -> data -> start_time_ms), philo -> id, diff);
			dead = 0;
	}
	return (dead);
}

int	p_check_if_any_are_dead(t_data *data)
{
	int	i;
	
	i = 0;
	pthread_mutex_lock(&data -> mutex);
	while (i < data -> num_philos)
	{
		if (p_is_dead(data -> philos[i]))
		{
			// add print here? or in is_dead?
			return (pthread_mutex_unlock(&data -> mutex), 1);
		}
		i++;
	}
	pthread_mutex_unlock(&data -> mutex);
	return (0);
}

void	*p_monitoring_thread(void *data_struct)
{
	t_data	*data;

	data = (t_data *)data_struct;
	while (1)
	{
		if (p_check_if_any_are_dead(data))
			return (p_stop_program(data), NULL);
	}
	return (NULL);	
}
