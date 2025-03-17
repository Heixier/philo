/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:13:14 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/17 19:38:51 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	p_announce(t_data *data, int id, char *msg)
{
	pthread_mutex_lock(&data -> check_status);
	if (data -> stop_flag)
		return (pthread_mutex_unlock(&data -> check_status), FAILURE);
	pthread_mutex_unlock(&data -> check_status);
	pthread_mutex_lock(&data -> microphone);
	printf("%d %d %s\n", p_get_timestamp(data -> start_time_ms), id, msg);
	pthread_mutex_unlock(&data -> microphone);
	return (SUCCESS);
}

// Just to print the final message after the program has stopped
void	p_sudo_announce(t_data *data, int id, char *msg)
{
	pthread_mutex_lock(&data -> microphone);
	printf("%d %d %s\n", p_get_timestamp(data -> start_time_ms), id, msg);
	pthread_mutex_unlock(&data -> microphone);
}

void	p_error_announce(t_data *data, char *err)
{
	pthread_mutex_lock(&data -> microphone);
	write(2, err, ft_strlen(err));
	pthread_mutex_unlock(&data -> microphone);
}