/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_actions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:26:49 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/20 21:51:15 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*p_philo_thread(void *philo_struct)
{
	t_philo	*philo;
	int		id;

	philo = (t_philo *)philo_struct;
	id = philo -> id;
	pthread_mutex_lock(&philo -> data -> data);
	philo -> last_eat_ms = p_get_time_ms();
	pthread_mutex_lock(&philo -> data -> print);
	printf("Intialised philo %d time_to_eat to %d\n", philo -> id, p_get_timestamp(philo -> data -> start_time_ms));
	pthread_mutex_unlock(&philo -> data -> print);
	pthread_mutex_unlock(&philo -> data -> data);
	while (1)
	{
		if (id % 2 == 0)
		{
			if (!p_even_philo_actions(philo))
				return (NULL);
		}
		else
		{
			if (!p_odd_philo_actions(philo))
				return (NULL);
		}
		// pthread_mutex_lock(&philo -> data -> mutex);
		// p_print_debug_individual(philo);
		// pthread_mutex_unlock(&philo -> data -> mutex);
	}
	return (NULL);
}

// Grab right then left
int	p_even_philo_actions(t_philo *philo)
{
	if (p_check_if_stopped(philo -> data))
		return (0);
	if (!p_grab_forks(philo, \
		(philo -> id + 1) % philo -> data -> num_philos, philo -> id))
		return (0);
	if (!p_eat(philo))
		return (0);
	p_put_down_forks(philo -> data, \
		(philo -> id + 1) % philo -> data -> num_philos, philo -> id);
	if (p_check_if_stopped(philo -> data))
		return (0);
	if (!p_sleep(philo))
		return (0);
	if (p_check_if_stopped(philo -> data))
		return (0);
	p_announce(philo -> data, philo -> id, "is thinking");
	return (1);
}

// Grab left then right
int	p_odd_philo_actions(t_philo *philo)
{
	if (p_check_if_stopped(philo -> data))
		return (0);
	if (!p_grab_forks(philo, philo -> id, \
		(philo -> id + 1) % philo -> data -> num_philos))
		return (0);
	if (!p_eat(philo))
		return (p_put_down_forks(philo -> data, philo -> id, \
			(philo -> id + 1) % philo -> data -> num_philos), 0);
	p_put_down_forks(philo -> data, philo -> id, \
		(philo -> id + 1) % philo -> data -> num_philos);
	if (!p_sleep(philo))
		return (0);
	if (p_check_if_stopped(philo -> data))
		return (0);
	p_announce(philo -> data, philo -> id, "is thinking");
	return (1);
}

// Left fork is defined as id, right fork is id + 1
int	p_grab_forks(t_philo *philo, int first_id, int second_id)
{
	pthread_mutex_lock(&philo -> data -> forks[first_id]);
	p_announce(philo -> data, philo -> id, "has taken a fork");
	if (p_check_if_stopped(philo -> data))
	{
		pthread_mutex_unlock(&philo -> data -> forks[first_id]);
		return (FAILURE);
	}
	// pthread_mutex_lock(&philo -> data -> data);
	// printf("%d first fork taken at %ld\n", philo -> id, p_get_time_ms());
	// pthread_mutex_unlock(&philo -> data -> data);
	pthread_mutex_lock(&philo -> data -> forks[second_id]);
	if (p_check_if_stopped(philo -> data))
	{
		pthread_mutex_unlock(&philo -> data -> forks[first_id]);
		pthread_mutex_unlock(&philo -> data -> forks[second_id]);
		return (FAILURE);
	}
	p_announce(philo -> data, philo -> id, "has taken a fork");
	// pthread_mutex_lock(&philo -> data -> data);
	// printf("%d second fork taken at %ld\n", philo -> id, p_get_time_ms());
	// pthread_mutex_unlock(&philo -> data -> data);
	return (SUCCESS);
}

void	p_put_down_forks(t_data *data, int first_id, int second_id)
{
	pthread_mutex_unlock(&data -> forks[first_id]);
	pthread_mutex_unlock(&data -> forks[second_id]);
}

int	p_eat(t_philo *philo)
{
	if (p_check_if_stopped(philo -> data))
		return (0);
	pthread_mutex_lock(&philo -> data -> data);
	philo -> last_eat_ms = p_get_time_ms();
	philo -> times_eaten++;
	pthread_mutex_unlock(&philo -> data -> data);
	p_announce(philo -> data, philo -> id, "is eating");
	p_tick_sleep(philo -> data -> time_to_eat_ms);
	return (1);
}

int	p_sleep(t_philo *philo)
{
	if (p_check_if_stopped(philo -> data))
		return (0);
	p_announce(philo -> data, philo -> id, "is sleeping");
	p_tick_sleep(philo -> data -> time_to_sleep_ms);
	return (1);
}
