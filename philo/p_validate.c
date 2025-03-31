/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_validate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:45:05 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/31 14:21:41 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	p_check_philo_under_limit(int philos);

int	p_validate(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (write(2, \
			"\e[38;5;160;1mInvalid argument count!\n\e[38;5;117;1mUsage:\n\
number_of_philosophers time_to_die time_to_eat time_to_sleep \
minimum_times_to_eat(optional)\e[0m\n", 154), FAILURE);
	if (!p_check_philo_under_limit(ft_atoi(argv[i])))
		return (FAILURE);
	while (argv[i])
	{
		if (!ft_aredigits(argv[i]) || (ft_atoi(argv[i]) < 0))
			return (write(2, \
			"\e[38;5;160;1mOnly \e[1m\e[4mpositive \
integers\e[24m accepted\n\e[0m", 63), FAILURE);
		i++;
	}
	return (SUCCESS);
}

static int	p_check_philo_under_limit(int philos)
{
	if (philos > PHILO_LIMIT)
		return (write(2, \
			"\e[38;5;160;1mError! Too many philosophers\e[0m\n", 47), FAILURE);
	return (1);
}
