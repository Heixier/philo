/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_time.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:18:02 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/20 21:15:41 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Returns the current timestamp in ms
int	p_get_timestamp(uintptr_t start_time)
{
	return (p_get_time_ms() - start_time);
}

// Sets the start_time in data, also returns if needed
uintptr_t	p_set_start_time(t_data *data)
{
	uintptr_t	time;

	time = p_get_time_ms();
	data -> start_time_ms = time;
	return (time);
}

// tick more accurately
void	p_tick_sleep(int wait_time_ms)
{
	uintptr_t	wait_time_us;
	uintptr_t	elapsed;

	elapsed = 0;
	wait_time_us = wait_time_ms * 1000;
	while (elapsed < wait_time_us)
	{
		usleep(TIME_INCREMENT);
		elapsed += TIME_INCREMENT;
	}
}

// Do not spam this, gettimeofday is expensive
uintptr_t	p_get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

// // Sleep until timestamp
// void	p_sleep_until(uintptr_t delay_ms)
// {
// 	struct 		timeval tv;
// 	uintptr_t	curr;

// 	gettimeofday(&tv, NULL);
// 	while (tv.tv_usec)
// }
