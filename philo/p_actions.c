/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_actions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:26:49 by rsiah             #+#    #+#             */
/*   Updated: 2025/04/07 19:08:06 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	p_single_philo(t_philo *philo);

void	*p_philo_thread(void *philo_struct)
{
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
	pthread_mutex_lock(&philo->data->start_mutex);
	pthread_mutex_unlock(&philo->data->start_mutex);
	if (philo->data->num_philos == 1)
		p_single_philo(philo);
	else
	{
		while (1)
		{
			if (p_check_if_dead(philo))
				break ;
			p_eat(philo);
			if (p_check_if_dead(philo))
				break ;
			p_sleep(philo);
			if (p_check_if_dead(philo))
				break ;
			p_think(philo);
		}
	}
	return (NULL);
}

static void	p_single_philo(t_philo *philo)
{
	p_announce(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->data->death_flag = 1;
	pthread_mutex_unlock(&philo->data->death_mutex);
	p_tick_sleep(philo->data->time_to_die_ms, philo->data);
}

void	p_sleep(t_philo *philo)
{
	p_announce(philo, "is sleeping");
	p_tick_sleep(philo->data->time_to_sleep_ms, philo->data);
}

// No thinky it works without it
void	p_think(t_philo *philo)
{
	p_announce(philo, "is thinking");
	p_tick_sleep(philo->data->time_to_eat_ms - \
		philo->data->time_to_sleep_ms, philo->data);
}
