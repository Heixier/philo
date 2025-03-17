/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_philo_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:57:13 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/17 16:54:32 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	p_eat(t_philo *philo);
static void	p_sleep(t_philo *philo);

// Thread
void	*p_philo(void *philo_struct)
{
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
	while (!philo -> data -> start_flag && !philo -> data -> stop_flag)
		;
		// p_announce(philo -> data, philo -> id, "is spinning");
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

// Delay odd numbers, even starts first
static void	p_eat(t_philo *philo)
{
	if (philo -> id % 2 == 0)
	{
		pthread_mutex_lock(&philo -> data -> forks[philo -> id]);
		p_announce(philo -> data, philo -> id, "has taken a fork");
		pthread_mutex_lock(&philo -> data -> \
			forks[(philo -> id + 1) % (philo -> data -> num_philos)]);
		p_announce(philo -> data, philo -> id, "has taken a fork");
	}
	else
	{
		p_tick_sleep(philo -> offset_ms);
		philo -> offset_ms = 0;
		pthread_mutex_lock(&philo -> data -> \
			forks[(philo -> id + 1) % (philo -> data -> num_philos)]);
		p_announce(philo -> data, philo -> id, "has taken a fork");
		pthread_mutex_lock(&philo -> data -> forks[philo -> id]);
		p_announce(philo -> data, philo -> id, "has taken a fork");
	}
	p_tick_sleep(philo -> data -> time_to_eat_ms);
	philo -> last_eat_ms = p_get_time_ms();
	philo -> times_eaten++;
	pthread_mutex_unlock(&philo -> data -> forks[philo -> id]);
	pthread_mutex_unlock(&philo -> data -> \
		forks[(philo -> id + 1) % (philo -> data -> num_philos)]);
}

static void	p_sleep(t_philo *philo)
{
	p_announce(philo -> data, philo -> id, "is sleeping");
	p_tick_sleep(philo -> data -> time_to_sleep_ms);
}
