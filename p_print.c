/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:13:14 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/17 16:55:29 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	p_announce(t_data *data, int id, char *msg)
{
	if (data -> stop_flag)
		return (FAILURE);
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
