/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:44:08 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/22 21:37:03 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Start from here
t_data	*p_init_philo_data(int argc, char **argv)
{
	t_data	*data;

	if (!p_validate(argc, argv))
		return (NULL);
	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		return (p_error_announce(data, "fatal error: cgoh\n"), NULL);
	data -> num_philos = ft_atoi(argv[1]);
	data -> time_to_die_ms = ft_atoi(argv[2]);
	data -> time_to_eat_ms = ft_atoi(argv[3]);
	data -> time_to_sleep_ms = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data -> eat_limit_flag = 1;
		data -> eat_limit = ft_atoi(argv[5]);
	}
	if (!p_init_philosophers(data))
		return (free(data), NULL);
	if (!p_initialise_mutexes(data))
		return (p_free_philosophers(data), free(data), NULL);
	return (data);
}

// Initialises each philosopher and offsets the odd ones so they start later
t_data	*p_init_philosophers(t_data *data)
{
	int	i;

	data -> philos = ft_calloc(sizeof(t_philo *), data -> num_philos + 1);
	if (!data -> philos)
		return (NULL);
	i = 0;
	while (i < data -> num_philos)
	{
		data -> philos[i] = ft_calloc(sizeof(t_philo), 1);
		if (!data -> philos[i])
			return (p_error_announce(data, "fatal error: cgoh\n"), \
			p_free_philosophers(data), NULL);
		data -> philos[i] -> id = i;
		data -> philos[i] -> data = data;
		if (pthread_mutex_init(&data -> philos[i] -> lock, NULL))
		{
			p_destroy_partial_locks(data -> philos[i], i);
			p_free_philosophers(data);
			return (NULL);
		}
		i++;
	}
	return (data);
}

t_data	*p_initialise_mutexes(t_data *data)
{
	int	forks;
	int err;

	data -> forks = ft_calloc(sizeof(pthread_mutex_t), data -> num_philos);
	if (!data -> forks)
		return (NULL);
	// if (pthread_mutex_init(&data -> data, NULL) != 0)
	// 	return (p_error_announce(data, "fatal error: cgoh\n"), NULL);
	// if (pthread_mutex_init(&data -> print, NULL) != 0)
	// {
	// 	pthread_mutex_destroy(&data -> data);
	// 	return (p_error_announce(data, "fatal error: cgoh\n"), NULL);
	// }
	forks = 0;
	while (forks < data -> num_philos)
	{
		err = pthread_mutex_init(&data -> forks[forks], NULL);
		if (err != 0)
		{
			p_destroy_partial_forks(data, forks);
			// pthread_mutex_destroy(&data -> data);
			// pthread_mutex_destroy(&data -> print);
			return (write(2, "fatal error: cgoh\n", 19), free(data->forks), NULL);
		}
		forks++;
	}
	return (data);
}
