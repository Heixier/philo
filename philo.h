/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:04:41 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/15 18:25:33 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	microphone;
	t_philo			*philos;
	long long		start_time;
	int				stop_flag;
	int				eat_limit_flag;
	int				num_philos;
}				t_data;

typedef struct s_philo
{
	long long	eating_usec;
	long long	sleeping_usec;
	int			id;
	int			times_eaten;
	int			max_hunger;
	int			hunger;
	int			death_flag;
	int			offset;
	t_data		*data;
}				t_philo;

// Print
int			p_announce(t_data *data, char *id, char *msg);

// Time
long long	p_get_timestamp(long long start_time);
long long	p_set_start_time(t_data *data);

#endif
