/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_run_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:36:04 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/29 18:49:32 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	p_start_philosopher_threads(t_data *data)
{
	int			i;
	pthread_t	*thread_ids;

	i = 0;
	thread_ids = ft_calloc(sizeof(pthread_t), data -> num_philos + MON_THREADS);
	if (!thread_ids)
		return (p_error_announce(data, "malloc error\n"), FAILURE);
	data -> start_time_ms = p_get_time_ms();
	pthread_mutex_lock(&data -> start_mutex);
	pthread_create(&thread_ids[data -> num_philos], NULL, p_monitoring_thread, data);
	while (i < data -> num_philos)
	{
		pthread_create(&thread_ids[i], NULL, p_philo_thread, data -> philos[i]);
		i++;
	}
	i = 0;
	while (i < data -> num_philos)
	{
		data -> philos[i] -> last_eat_ms = p_get_time_ms();
		i++;
	}
	pthread_mutex_unlock(&data -> start_mutex);
	p_join_threads(thread_ids, data -> num_philos);
	free(thread_ids);
	return (SUCCESS);
}

int	p_join_threads(pthread_t *thread_ids, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(thread_ids[i], NULL);
		i++;
	}
	pthread_join(thread_ids[count], NULL);
	return (SUCCESS);
}
