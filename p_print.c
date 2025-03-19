/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:13:14 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/19 14:48:09 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// WARNING: WILL LOCK MUTEX; DO NOT USE IF ALREADY MUTEX
int	p_announce(t_data *data, int id, char *msg)
{
	pthread_mutex_lock(&data -> mutex);
	if (data -> stop_flag)
		return (pthread_mutex_unlock(&data -> mutex), FAILURE);
	printf("%d %d %s\n", p_get_timestamp(data -> start_time_ms), id, msg);
	pthread_mutex_unlock(&data -> mutex);
	return (SUCCESS);
}

// Just to print the final message after the program has stopped
void	p_sudo_announce(t_data *data, int id, char *msg)
{
	pthread_mutex_lock(&data -> mutex);
	printf("%d %d %s\n", p_get_timestamp(data -> start_time_ms), id, msg);
	pthread_mutex_unlock(&data -> mutex);
}

void	p_error_announce(t_data *data, char *err)
{
	pthread_mutex_lock(&data -> mutex);
	write(2, err, ft_strlen(err));
	pthread_mutex_unlock(&data -> mutex);
}
