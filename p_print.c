/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:13:14 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/15 21:18:09 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	p_announce(t_data *data, char *id, char *msg)
{
	if (data -> stop_flag)
		return (NULL);
	pthread_mutex_lock(&data -> microphone);
	printf("%lld %s %s\n", p_get_timestamp(data -> start_time), id, msg);
	pthread_mutex_unlock(&data -> microphone);
}

// Just to print the final message after the program has stopped
int	p_sudo_announce(t_data *data, char *id, char *msg)
{
	pthread_mutex_lock(&data -> microphone);
	printf("%lld %s %s\n", p_get_timestamp(data -> start_time), id, msg);
	pthread_mutex_unlock(&data -> microphone);
}
