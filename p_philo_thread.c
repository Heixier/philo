/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_philo_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:57:13 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/17 20:05:43 by rsiah            ###   ########.fr       */
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
	while (1)
	{
		if (p_check_if_stopped(philo -> data) || philo -> death_flag)
			return (NULL);
		// Not dead
		p_eat(philo);
		if (p_check_if_stopped(philo -> data) || philo -> death_flag)
			return (NULL);
		p_sleep(philo);
		if (p_check_if_stopped(philo -> data) || philo -> death_flag)
			return (NULL);
		p_announce(philo -> data, philo -> id, "is thinking");
	}
}

// Delay odd numbers, even starts first
static void	p_eat(t_philo *philo)
{
	if (philo -> id % 2 == 0)
	{
		// philo -> offset_ms = 1;
		// p_tick_sleep(philo -> offset_ms);
		// philo -> offset_ms = 0;
		pthread_mutex_lock(&philo -> data -> forks[philo -> id]);
		p_announce(philo -> data, philo -> id, "has taken a first fork");
		if (p_check_if_stopped(philo -> data))
		{
			pthread_mutex_unlock(&philo -> data -> forks[philo ->id]);
			return ;
		}
		pthread_mutex_lock(&philo -> data -> \
			forks[(philo -> id + 1) % (philo -> data -> num_philos)]);
		p_announce(philo -> data, philo -> id, "has taken a second fork");
	}
	else
	{
		philo -> offset_ms = 1;
		// p_tick_sleep(philo -> offset_ms);
		p_tick_sleep(philo -> offset_ms);
		// philo -> offset_ms = 0;
		pthread_mutex_lock(&philo -> data -> \
			forks[(philo -> id + 1) % (philo -> data -> num_philos)]);
		p_announce(philo -> data, philo -> id, "has taken a first fork");
		if (p_check_if_stopped(philo -> data))
		{
			pthread_mutex_unlock(&philo -> data -> forks[philo ->id]);
			return ;
		}
		pthread_mutex_lock(&philo -> data -> forks[philo -> id]);
		p_announce(philo -> data, philo -> id, "has taken a second fork");
	}
	p_announce(philo -> data, philo -> id, "is eating");
	philo -> last_eat_ms = p_get_time_ms();
	philo -> times_eaten++;
	p_tick_sleep(philo -> data -> time_to_eat_ms);
	pthread_mutex_unlock(&philo -> data -> forks[philo -> id]);
	pthread_mutex_unlock(&philo -> data -> \
		forks[(philo -> id + 1) % (philo -> data -> num_philos)]);
}

static void	p_sleep(t_philo *philo)
{
	p_announce(philo -> data, philo -> id, "is sleeping");
	p_tick_sleep(philo -> data -> time_to_sleep_ms);
}
