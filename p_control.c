/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_control.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:34:07 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/18 16:29:19 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_stop_program(t_data *data)
{
	pthread_mutex_lock(&data -> mutex);
	data -> stop_flag = 1;
	pthread_mutex_unlock(&data -> mutex);
}

int	p_check_if_stopped(t_data *data)
{
	int	state;

	pthread_mutex_lock(&data -> mutex);
	state = data -> stop_flag;
	pthread_mutex_unlock(&data -> mutex);
	return (state);
}
