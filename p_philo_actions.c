/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_philo_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:26:49 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/18 16:08:10 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*p_philo_thread(void *philo_struct)
{
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
	pthread_mutex_lock(&philo -> data -> edit);
	philo -> last_eat_ms = p_get_time_ms();
	pthread_mutex_unlock(&philo -> data -> edit);
	pthread_mutex_lock(&philo -> data -> microphone);
	p_print_debug_individual(philo);
	pthread_mutex_unlock(&philo -> data -> microphone);
	return (NULL);
}
