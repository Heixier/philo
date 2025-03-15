/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_monitoring_thread.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:34:29 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/15 18:47:16 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*p_reaper_thread(void *data_struct)
{
	t_data	*data;

	data = (t_data *)data_struct;
	p_tick_hunger(data);
	return (NULL);
}

void	p_tick_hunger(t_data *data)
{
	int	i;

	i = 0;
	while (!data -> stop_flag)
	{
		p_decrement_all_hunger(data);
		usleep(1000);
	}
}

void	p_decrement_all_hunger(t_data *data)
{
	int	i;

	i = 0;
	while (i < data -> num_philos)
	{
		data -> philos[i].hunger--;
		i++;
	}
}