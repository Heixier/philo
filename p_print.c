/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:13:14 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/30 18:18:51 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// LOCKS BOTH DATA AND PRINT MUTEXES
int	p_announce(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo -> data -> print_mutex);
	if (!p_check_if_dead(philo))
		printf("%d %d %s\n", p_get_timestamp(philo -> data -> start_time_ms), \
		philo -> id, msg);
	pthread_mutex_unlock(&philo -> data -> print_mutex);
	return (SUCCESS);
}

int	p_sudo_announce(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo -> data -> print_mutex);
	printf("%d %d %s\n", p_get_timestamp(philo -> data -> start_time_ms), \
	philo -> id, msg);
	pthread_mutex_unlock(&philo -> data -> print_mutex);
	return (SUCCESS);
}

void	p_error_announce(t_data *data, char *err)
{
	pthread_mutex_lock(&data -> print_mutex);
	write(2, err, ft_strlen(err));
	pthread_mutex_unlock(&data -> print_mutex);
}
