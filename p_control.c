/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_control.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:34:07 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/19 20:51:06 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_stop_program(t_data *data)
{
	pthread_mutex_lock(&data -> data);
	data -> stop_flag = 1;
	pthread_mutex_unlock(&data -> data);
}

int	p_check_if_stopped(t_data *data)
{
	int	state;

	pthread_mutex_lock(&data -> data);
	state = data -> stop_flag;
	pthread_mutex_unlock(&data -> data);
	return (state);
}
