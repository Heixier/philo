/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_monitoring.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:06:57 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/27 17:45:12 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*p_monitoring_thread(void *data_struct)
{
	int		i;
	t_data	*data;

	data = (t_data *)data;

	i = 0;
	while (!p_search_for_dead(data) || !p_check_eat_limit(data))
		;
	return (NULL);
}

// Returns 1 if dead philosopher is found
int	p_search_for_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data -> num_philos)
	{
		if (p_check_if_dead(data -> philos[i]))
		{
			p_announce(data -> philos[i], "has died");
			pthread_mutex_lock(&data -> death_mutex);
			data -> death_flag = 1;
			pthread_mutex_unlock(&data -> death_mutex);
			return (1);
		}
	}
}

int	p_check_eat_limit(t_data *data)
{
	int	i;

	i = 0;
	if (!data -> eat_limit_flag)
		return (0);
	while (i < data -> num_philos)
	{
		
	}
}