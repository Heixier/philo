/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_monitoring_thread.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:34:29 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/17 17:52:24 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	p_check_stop_condition(t_data *data);
static void	p_kill_philosopher_and_stop(t_data *data, int id);

// Monitoring thread
void	*p_reaper_thread(void *data_struct)
{
	t_data	*data;

	data = (t_data *)data_struct;
	while (!data -> start_flag && !data -> stop_flag)
		;
	while (!data -> stop_flag)
		p_check_stop_condition(data);
	return (NULL);
}

static void	p_check_stop_condition(t_data *data)
{
	int	i;
	int	hit_eating_limit;

	i = 0;
	hit_eating_limit = 0;
	while (i < data -> num_philos)
	{
		if (p_get_time_ms() - data -> philos[i] -> last_eat_ms >= \
		(uintptr_t)(data -> time_to_die_ms))
		{
			// printf("philosopher %d last ate at %ld (%ldms ago)\n", i, \
			// 	data -> philos[i] -> last_eat_ms, \
			// 	p_get_time_ms() - data -> philos[i] -> last_eat_ms);
			p_kill_philosopher_and_stop(data, i);
		}
		if (data -> eat_limit_flag)
		{
			if (data -> philos[i] -> times_eaten >= data -> eat_limit)
				hit_eating_limit++;
			if (hit_eating_limit == data -> num_philos)
			{
				data -> stop_flag = 1;
				p_sudo_announce(data, i, "temp: all philosophers have eaten!");
			}
		}
		i++;
	}
}

static void	p_kill_philosopher_and_stop(t_data *data, int id)
{
	data -> stop_flag = 1;
	data -> philos[id] -> death_flag = 1;
	p_sudo_announce(data, id, "died");
}
