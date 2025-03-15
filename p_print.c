/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:13:14 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/15 18:33:54 by rsiah            ###   ########.fr       */
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

// Just in case I need to print a final msg; should not need this function
int	p_sudo_announce(t_data *data, char *id, char *msg)
{
	pthread_mutex_lock(&data -> microphone);
	printf("%lld %s %s\n", p_get_timestamp(data -> start_time), id, msg);
	pthread_mutex_unlock(&data -> microphone);
}
