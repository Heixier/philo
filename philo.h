/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:04:41 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/19 14:26:01 by rsiah            ###   ########.fr       */
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
# define MON_THREADS 1

typedef struct s_philo	t_philo;

typedef struct s_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex;
	t_philo			**philos;
	uintptr_t		start_time_ms;
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

// Init
t_data		*p_init_philo_data(int argc, char **argv);
t_data		*p_init_philosophers(t_data *data);
t_data		*p_initialise_mutexes(t_data *data);

// Threads

// Lib
int			ft_aredigits(char *str);
int			ft_isdigit(int c);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_atoi(const char *nptr);

size_t		ft_strlen(const char *s);

// Print
int			p_announce(t_data *data, int id, char *msg);
void		p_sudo_announce(t_data *data, int id, char *msg);
void		p_error_announce(t_data *data, char *err);


void		p_print_debug(t_data *data);
void		p_print_debug_individual(t_philo *philo);

// Time
int			p_get_timestamp(uintptr_t start_time);
uintptr_t	p_set_start_time(t_data *data);
uintptr_t	p_get_time_ms(void);
void		p_tick_sleep(int wait_time_ms);

// Validate
int			p_validate(int argc, char **argv);

// Cleanup
void		p_cleanup(t_data *data);
void		p_destroy_mutexes(t_data *data);
void		p_destroy_partial_forks(t_data *data, int forks_created_so_far);
void		p_free_philosophers(t_data *data);

// Control
void		p_stop_program(t_data *data);
int			p_check_if_stopped(t_data *data);



// Threads

int		p_start_philosopher_threads(t_data *data);
void	*p_philo_thread(void *philo_struct);
int		p_join_threads(pthread_t *thread_ids, int count);

int		p_is_dead(t_philo *philo);
int		p_check_if_any_are_dead(t_data *data);
void	*p_monitoring_thread(void *data_struct);

#endif
