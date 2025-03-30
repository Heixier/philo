/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_actions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:26:49 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/29 20:04:34 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	p_take_even(t_philo *philo);
static void	p_take_odd(t_philo *philo);

void	*p_philo_thread(void *philo_struct)
{
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
	pthread_mutex_lock(&philo -> data -> start_mutex);
	pthread_mutex_unlock(&philo -> data -> start_mutex);
	if (philo -> data -> num_philos == 1)
	{
		p_announce(philo, "has taken a fork");
		pthread_mutex_lock(&philo -> data -> death_mutex);
		philo -> data -> death_flag = 1;
		pthread_mutex_unlock(&philo -> data -> death_mutex);
		p_tick_sleep(philo -> data -> time_to_die_ms);
	}
	else
	{
		while (1)
		{
			if (p_check_if_dead(philo))
				break;
			p_eat(philo);
			if (p_check_if_dead(philo))
				break;
			p_sleep(philo);
			if (p_check_if_dead(philo))
				break;
			p_think(philo);
		}
	}
	return (NULL);
}

static void	p_take_even(t_philo *philo)
{
	pthread_mutex_lock(&philo -> data -> forks[(philo -> id + 1) % philo -> data -> num_philos]);
	p_announce(philo, "has taken a fork");
	pthread_mutex_lock(&philo -> data -> forks[philo -> id]);
	p_announce(philo, "has taken a fork");
}

static void	p_take_odd(t_philo *philo)
{
	usleep(100);
	pthread_mutex_lock(&philo -> data -> forks[philo -> id]);
	p_announce(philo, "has taken a fork");
	pthread_mutex_lock(&philo -> data -> forks[(philo -> id + 1) % philo -> data -> num_philos]);
	p_announce(philo, "has taken a fork");
}

void	p_take_forks(t_philo *philo)
{
	if (philo -> id % 2)
		p_take_odd(philo);
	else
		p_take_even(philo);
}

void	p_eat(t_philo *philo)
{
	p_take_forks(philo);
	p_announce(philo, "is eating");
	pthread_mutex_lock(&philo -> eat_mutex);
	philo -> last_eat_ms = p_get_time_ms();
	philo -> times_eaten++;
	pthread_mutex_unlock(&philo -> eat_mutex);
	p_tick_sleep(philo -> data -> time_to_eat_ms);
	p_unlock_forks(philo);
}

void	p_unlock_forks(t_philo *philo)
{
	if (philo -> id % 2)
	{
		pthread_mutex_unlock(&philo -> data -> forks[philo -> id]);
		pthread_mutex_unlock(&philo -> data -> forks[(philo -> id + 1) % philo -> data -> num_philos]);
	}
	else
	{
		pthread_mutex_unlock(&philo -> data -> forks[philo -> id]);
		pthread_mutex_unlock(&philo -> data -> forks[(philo -> id + 1) % philo -> data -> num_philos]);
	}
}

void	p_sleep(t_philo *philo)
{
	p_announce(philo, "is sleeping");
	p_tick_sleep(philo -> data -> time_to_sleep_ms);
}

// Think for a moment before continuing will this cause drift?
void	p_think(t_philo *philo)
{
	p_announce(philo, "is thinking");
	// usleep(100);
}
