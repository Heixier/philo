/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_time.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:18:02 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/15 18:49:17 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Returns the current timestamp in ms
long long	p_get_timestamp(long long start_time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - start_time);
}

// Sets the start_time in data, also returns if needed
long long	p_set_start_time(t_data *data)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	data -> start_time = time;
	return (time);
}

// tick more accurately, spam a get timeofday with a small usleep until we reach 1000
int		tick_in_ms()