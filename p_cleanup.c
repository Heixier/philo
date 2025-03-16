/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_cleanup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:43:25 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/16 18:52:00 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_free_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data -> num_philos)
	{
		free(data -> philos[i]);
		i++;
	}
}

// Final cleanup assuming everything was successfully initialised
void	p_cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (data -> philos[i])
	{
		free(data -> philos[i]);
		i++;
	}
	free(data -> philos);
	pthread_mutex_destroy(&data -> microphone)
}