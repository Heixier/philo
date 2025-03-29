/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_time.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:18:02 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/29 18:56:36 by rsiah            ###   ########.fr       */
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
	uintptr_t	start;
	int	elapsed;

	start = p_get_time_ms();
	elapsed = 0;
	while (elapsed < wait_time_ms)
	{
		elapsed = p_get_time_ms() - start;
		usleep(10);
	}
}

uintptr_t	p_get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
