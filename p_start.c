/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_start.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:45:18 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/17 20:00:28 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Sets all our starting timings, then lets the threads go
void	p_readysetgo(t_data *data)
{
	int	i;
	uintptr_t	start_ms;

	i = 0;
	start_ms = p_set_start_time(data);
	// printf("start_ms: %ld\n", start_ms);
	while (i < data -> num_philos)
	{
		data -> philos[i] -> last_eat_ms = start_ms;
		i++;
	}
	// pthread_mutex_lock(&data -> microphone);
	// printf("Program starting at %lu\n", data -> start_time_ms);
	// pthread_mutex_unlock(&data -> microphone);
	// sleep(1);
	data -> start_flag = 1;
}

// Creates and starts the threads, returns 0 on failure
int	p_start_threads(t_data *data)
{
	int			i;
	pthread_t	*thread_array;
	
	thread_array = p_create_pthread_array(data -> num_philos + 1);
	if (!thread_array)
		return (p_error_announce(data, "fatal error: cgoh\n"), FAILURE);
	i = 0;
	while (i < data -> num_philos)
	{
		if (pthread_create(&thread_array[i], NULL, p_philo, data -> philos[i]) != 0)
		{
			
			p_stop_program(data);
			p_error_announce(data, "error: pthread\n");
			return (p_pthread_partial_cleanup(thread_array, i), FAILURE);
		}
		i++;
	}

	if (!p_create_reaper_thread(thread_array, data))
		return (FAILURE);
	p_readysetgo(data);
	p_join_threads(thread_array, data -> num_philos + 1);
	return (free(thread_array), SUCCESS);
}

// Create the additional monitoring thread at the end of the array
int	p_create_reaper_thread(pthread_t *thread_array, t_data *data)
{
	if (pthread_create(&thread_array[data -> num_philos], \
		NULL, p_reaper_thread, data) != 0)
	{
		p_stop_program(data);
		p_error_announce(data, "error: pthread\n");
		return (p_pthread_partial_cleanup(thread_array, data -> num_philos), 0);
	}
	return (SUCCESS);
}

void	p_join_threads(pthread_t *thread_array, int num_threads)
{
	int	i;

	i = 0;
	while (i < num_threads)
	{
		pthread_join(thread_array[i], NULL);
		i++;
	}
}

void	p_pthread_partial_cleanup(pthread_t *arr, int threads)
{
	int	i;

	i = 0;
	while (i < threads)
	{
		pthread_join(arr[i], NULL);
		i++;
	}
	free(arr);
}

pthread_t	*p_create_pthread_array(int	num_philos)
{
	pthread_t	*array;

	array = ft_calloc(sizeof(pthread_t), num_philos);
	if (!array)
		return (NULL);
	return (array);
}
