/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:13:14 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/19 20:26:41 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// LOCKS BOTH DATA AND PRINT MUTEXES
int	p_announce(t_data *data, int id, char *msg)
{
	pthread_mutex_lock(&data -> data);
	pthread_mutex_lock(&data -> print);
	if (!data -> stop_flag)
		printf("%d %d %s\n", p_get_timestamp(data -> start_time_ms), id, msg);
	pthread_mutex_unlock(&data -> print);
	pthread_mutex_unlock(&data -> data);
	return (SUCCESS);
}

// Just to print the final message after the program has stopped
void	p_sudo_announce(t_data *data, int id, char *msg)
{
	pthread_mutex_lock(&data -> data);
	pthread_mutex_lock(&data -> print);
	printf("%d %d %s\n", p_get_timestamp(data -> start_time_ms), id, msg);
	pthread_mutex_unlock(&data -> print);
	pthread_mutex_unlock(&data -> data);
}

void	p_error_announce(t_data *data, char *err)
{
	pthread_mutex_lock(&data -> data);
	pthread_mutex_lock(&data -> print);
	write(2, err, ft_strlen(err));
	pthread_mutex_unlock(&data -> print);
	pthread_mutex_unlock(&data -> data);
}
