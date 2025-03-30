/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_control.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:34:07 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/30 18:25:27 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	p_check_if_dead(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(&philo->data->death_mutex);
	status = philo->data->death_flag;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (status);
}
