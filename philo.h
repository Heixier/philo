/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:04:41 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/16 18:11:18 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>

# define SUCCESS 1
# define FAILURE 0

typedef struct s_philo	t_philo;

typedef struct s_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	microphone;
	t_philo			**philos;
	long long		start_time;
	int				stop_flag;
	int				num_philos;
	int				time_to_die_ms;
	int				time_to_eat_ms;
	int				time_to_sleep_ms;
	int				eat_limit_flag;
	int				eat_limit;
}				t_data;

typedef struct s_philo
{
	uintptr_t	last_eat_ms;
	int			id;
	int			times_eaten;
	int			death_flag;
	int			offset_ms;
	t_data		*data;
}				t_philo;

// Lib
int			ft_aredigits(char *str);
int			ft_isdigit(int c);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_atoi(const char *nptr);

// Print
int			p_announce(t_data *data, char *id, char *msg);

// Time
uintptr_t	p_get_timestamp(int start_time);
uintptr_t	p_set_start_time(t_data *data);
uintptr_t	p_get_time_ms(void);
void		p_tick_sleep(int wait_time_ms);

#endif
