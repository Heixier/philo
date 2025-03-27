/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_actions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:26:49 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/27 17:01:01 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*p_philo_thread(void *philo_struct)
{
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
	while (!p_check_if_dead(philo))
	{
		p_eat(philo);
		p_sleep(philo);
		p_think(philo);
	}
}

void	p_take_forks(t_philo *philo)
{
	if (philo -> data -> num_philos == 1 || philo -> id == 0)
		p_fork_grab_alt_cases(philo);
	else
	{
		pthread_mutex_lock(&philo -> data -> forks[philo -> id]);
		p_announce(philo, "has taken a fork");
		pthread_mutex_lock(&philo -> data -> forks[(philo -> id + 1) % philo -> data -> num_philos]);
		p_announce(philo, "has taken a fork");
	}
}

void	p_fork_grab_alt_cases(t_philo *philo)
{
	if (philo -> data -> num_philos == 1)
	{
		pthread_mutex_lock(&philo -> data -> forks[philo -> id]);
		p_announce(philo, "has taken a fork");
		p_tick_sleep(philo -> data -> time_to_die_ms);
		pthread_mutex_unlock(&philo -> data -> forks[philo -> id]);
		p_announce(philo, "has died");
		pthread_mutex_lock(&philo -> data -> death_mutex);
		philo -> data -> death_flag = 1;
		pthread_mutex_unlock(&philo -> data -> death_mutex);
	}
	else
		p_swap_fork_for_first_philo(philo);
}

// If philo id == 0, swap its forks
void	p_swap_fork_for_first_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo -> data -> forks[(philo -> id + 1) % philo -> data -> num_philos]);
	p_announce(philo, "has taken a fork");
	pthread_mutex_lock(&philo -> data -> forks[philo -> id]);
	p_announce(philo, "has taken a fork");
}

void	p_eat(t_philo *philo)
{
	p_take_forks(philo);
	p_announce(philo, "is eating");
	pthread_mutex_lock(&philo -> data -> eat_mutex);
	philo -> last_eat_ms = p_get_time_ms();
	pthread_mutex_unlock(&philo -> data -> eat_mutex);
	p_tick_sleep(philo -> data -> time_to_eat_ms);
	p_unlock_forks(philo);
}

void	p_unlock_forks(t_philo *philo)
{
	if (philo -> id == 0)
	{
		pthread_mutex_unlock(&philo -> data -> forks[(philo -> id + 1) % philo -> data -> num_philos]);
		pthread_mutex_unlock(&philo -> data -> forks[philo -> id]);
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
	p_annouce(philo, "is thinking");
	p_tick_sleep(10);
}
