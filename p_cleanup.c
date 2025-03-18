/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_cleanup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:43:25 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/18 15:33:12 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_free_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data -> num_philos)
	{
		free(data -> philos[i]);
		i++;
	}
}

// Destroy up to forks_created_so_far; latest fork failed to create
void	p_destroy_partial_forks(t_data *data, int forks_created_so_far)
{
	int	i;

	i = 0;
	while (i < forks_created_so_far)
	{
		pthread_mutex_destroy(&data -> forks[i]);
		i++;
	}
}

// Destroy all our forks and microphone
void	p_destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data -> num_philos)
	{
		pthread_mutex_destroy(&data -> forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data -> microphone);
	pthread_mutex_destroy(&data -> edit);
}

// Final cleanup assuming everything was successfully initialised
void	p_cleanup(t_data *data)
{
	int	i;

	i = 0;
	p_free_philosophers(data);
	free(data -> philos);
	p_destroy_mutexes(data);
	free(data -> forks);
	free(data);
	printf("cleanup complete\n");
}
