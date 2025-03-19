/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_actions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:26:49 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/19 21:33:57 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*p_philo_thread(void *philo_struct)
{
	t_philo	*philo;
	int		id;

	philo = (t_philo *)philo_struct;
	pthread_mutex_lock(&philo -> data -> data);
	philo -> last_eat_ms = p_get_time_ms(); // Set the last_eat to thread start
	id = philo -> id;
	p_print_debug_individual(philo);
	pthread_mutex_unlock(&philo -> data -> data);
	while (1)
	{
		if (p_check_if_stopped(philo -> data))
			return (NULL);
		if (id % 2 == 0)
		{
			if (!p_even_philo_actions(philo))
				return (NULL);
		}
		else
		{
			if (p_odd_philo_actions(philo))
				return (NULL);
		}
		// pthread_mutex_lock(&philo -> data -> mutex);
		// p_print_debug_individual(philo);
		// pthread_mutex_unlock(&philo -> data -> mutex);
	}
	return (NULL);
}

int	p_even_philo_actions(t_philo *philo)
{
	// tme to grab the forks and see what happens
	if (p_check_if_stopped(philo -> data))
		return (0);
	p_announce(philo -> data, philo -> id, "is thinking");
	p_tick_sleep(philo -> data -> time_to_eat_ms);
	if (p_check_if_stopped(philo -> data))
		return (0);
	p_announce(philo -> data, philo -> id, "is sleeping");
	p_tick_sleep(philo -> data -> time_to_sleep_ms);
	if (p_check_if_stopped(philo -> data))
		return (0);
	p_announce(philo -> data, philo -> id, "is thinking");
	return (1);
}

int	p_odd_philo_actions(t_philo *philo)
{
	// tme to grab the forks and see what happens
	if (p_check_if_stopped(philo -> data))
		return (0);
	p_announce(philo -> data, philo -> id, "is thinking");
	p_tick_sleep(philo -> data -> time_to_eat_ms);
	if (p_check_if_stopped(philo -> data))
		return (0);
	p_announce(philo -> data, philo -> id, "is sleeping");
	p_tick_sleep(philo -> data -> time_to_sleep_ms);
	if (p_check_if_stopped(philo -> data))
		return (0);
	p_announce(philo -> data, philo -> id, "is thinking");
	return (1);
}
