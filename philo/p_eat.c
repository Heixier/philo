/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_eat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:28:33 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/30 18:33:22 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	p_take_even(t_philo *philo);
static void	p_take_odd(t_philo *philo);
static void	p_take_forks(t_philo *philo);
static void	p_unlock_forks(t_philo *philo);

static void	p_take_even(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[(philo->id + 1) % \
		philo->data->num_philos]);
	p_announce(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[philo->id]);
	p_announce(philo, "has taken a fork");
}

static void	p_take_odd(t_philo *philo)
{
	usleep(100);
	pthread_mutex_lock(&philo->data->forks[philo->id]);
	p_announce(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[(philo->id + 1) % \
		philo->data->num_philos]);
	p_announce(philo, "has taken a fork");
}

static void	p_take_forks(t_philo *philo)
{
	if (philo->id % 2)
		p_take_odd(philo);
	else
		p_take_even(philo);
}

static void	p_unlock_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->id]);
		pthread_mutex_unlock(&philo->data->forks[(philo->id + 1) % \
			philo->data->num_philos]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[philo->id]);
		pthread_mutex_unlock(&philo->data->forks[(philo->id + 1) % \
			philo->data->num_philos]);
	}
}

void	p_eat(t_philo *philo)
{
	p_take_forks(philo);
	p_announce(philo, "is eating");
	pthread_mutex_lock(&philo->eat_mutex);
	philo->last_eat_ms = p_get_time_ms();
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->eat_mutex);
	p_tick_sleep(philo->data->time_to_eat_ms);
	p_unlock_forks(philo);
}
