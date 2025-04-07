/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_monitoring.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:06:57 by rsiah             #+#    #+#             */
/*   Updated: 2025/04/07 17:56:06 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	p_search_for_starved(t_data *data);
static int	p_check_eat_limit(t_data *data);

void	*p_mon_thread(void *data_struct)
{
	t_data	*data;

	data = (t_data *)data_struct;
	pthread_mutex_lock(&data->start_mutex);
	pthread_mutex_unlock(&data->start_mutex);
	while (!p_search_for_starved(data) && !p_check_eat_limit(data))
		usleep(1000);
	return (NULL);
}

// Returns true if philosopher has starved to death
static int	p_search_for_starved(t_data *data)
{
	int			i;
	uintptr_t	time_elapsed;

	i = 0;
	while (i < data -> num_philos)
	{
		pthread_mutex_lock(&data->philos[i]->eat_mutex);
		time_elapsed = p_get_time_ms() - data->philos[i]->last_eat_ms;
		pthread_mutex_unlock(&data->philos[i]->eat_mutex);
		if (time_elapsed > (uintptr_t)data->time_to_die_ms)
		{
			pthread_mutex_lock(&data->death_mutex);
			data -> death_flag = 1;
			pthread_mutex_unlock(&data->death_mutex);
			p_sudo_announce(data->philos[i], "died");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	p_check_eat_limit(t_data *data)
{
	int	i;
	int	eaten;

	i = 0;
	eaten = 0;
	if (!data -> eat_limit_flag)
		return (0);
	while (i < data -> num_philos)
	{
		pthread_mutex_lock(&data->philos[i]->eat_mutex);
		if (data -> philos[i]->times_eaten >= data->eat_limit)
			eaten++;
		pthread_mutex_unlock(&data->philos[i]->eat_mutex);
		i++;
	}
	if (eaten == data -> num_philos)
	{
		pthread_mutex_lock(&data->death_mutex);
		data -> death_flag = 1;
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}
