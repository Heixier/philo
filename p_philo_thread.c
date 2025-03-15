/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_philo_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:57:13 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/15 18:39:25 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Thread
void	*p_philo(void *philo_struct)
{
	t_philo	*philo;

	philo= (t_philo *)philo_struct;
	while (1)
	{
		if (philo -> data -> stop_flag|| philo -> death_flag)
			return (NULL);
		// Not dead
		p_eat(philo);
		if (philo -> data -> stop_flag || philo -> death_flag)
			return (NULL);
		p_sleep(philo);
		if (philo -> data -> stop_flag|| philo -> death_flag)
			return (NULL);
		p_announce(philo -> data, philo -> id, "is thinking");
	}
}

void	p_eat(t_philo *philo)
{
	if (philo -> id % 2)
	{
		pthread_mutex_lock(&philo -> data -> forks[philo -> id]);
		p_announce(philo -> data, philo -> id, "has taken a fork");
		pthread_mutex_lock(&philo -> data -> \
			forks[philo -> id + 1 % philo -> data -> num_philos]);
		p_announce(philo -> data, philo -> id, "has taken a fork");
	}
	else
	{
		usleep(philo -> offset);
		philo -> offset = 0;
		pthread_mutex_lock(&philo -> data -> \
			forks[philo -> id + 1 % philo -> data -> num_philos]);
		p_announce(philo -> data, philo -> id, "has taken a fork");
		pthread_mutex_lock(&philo -> data -> forks[philo -> id]);
		p_announce(philo -> data, philo -> id, "has taken a fork");
	}
	philo -> hunger += philo -> eating_usec * 2000; // Don't die while eating
	usleep(philo -> eating_usec);
	philo -> hunger = philo -> max_hunger;
	pthread_mutex_unlock(&philo -> data -> forks[philo -> id]);
	pthread_mutex_unlock(&philo -> data -> forks[philo -> id + 1]);
}

void	p_sleep(t_philo *philo)
{
	p_announce(philo -> data, philo -> id, "is sleeping");
	usleep(philo -> sleeping_usec);
}
