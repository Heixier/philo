/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 23:18:17 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/17 16:46:22 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	 main(int argc, char **argv)
{
	t_data	*data;

	data = p_init_philo_data(argc, argv);
	if (!data)
		return (1);
	if (!p_start_threads(data))
		return (1);
	p_cleanup(data);
	return (0);
}
