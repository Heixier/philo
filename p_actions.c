/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_actions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:26:49 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/19 14:47:30 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*p_philo_thread(void *philo_struct)
{
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
	pthread_mutex_lock(&philo -> data -> mutex);
	philo -> last_eat_ms = p_get_time_ms(); // Set the last_eat to thread start
	p_print_debug_individual(philo);
	pthread_mutex_unlock(&philo -> data -> mutex);
	// while (1)
	for (int i = 0; i < 3; i++)
	{
		p_announce(philo -> data, philo -> id, "is eating");
		p_tick_sleep(philo -> data -> time_to_die_ms);
		p_announce(philo -> data, philo -> id, "is sleeping");
		p_tick_sleep(philo -> data -> time_to_sleep_ms);
		p_announce(philo -> data, philo -> id, "is thinking");
		// pthread_mutex_lock(&philo -> data -> mutex);
		// p_print_debug_individual(philo);
		// pthread_mutex_unlock(&philo -> data -> mutex);
	}
	pthread_mutex_lock(&philo -> data -> mutex);
	printf("%d stopped at %dms\n", philo -> id, p_get_timestamp(philo -> data -> start_time_ms));
	pthread_mutex_unlock(&philo -> data -> mutex);
	return (NULL);
}
