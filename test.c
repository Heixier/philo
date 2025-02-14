/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:08:46 by rsiah             #+#    #+#             */
/*   Updated: 2025/02/14 15:25:18 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

void	*sleeper(void *arg)
{
	int	time;

	time = *((int *)arg);
	printf("Begin sleep for %d seconds\n", time);
	sleep(time);
	printf("Ended sleep of %d seconds\n", time);
	free(arg);
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t	thread_pid[2];
	int			error;
	int			*sleep_time;

	if (argc < 2)
		return (printf("Not enough args\n"), 1);
	for (int i = 0; i < 2; i++)
	{
		sleep_time = malloc(sizeof(int));
			if (!sleep_time)
				return (perror("malloc"), 1);
		*sleep_time = atoi(argv[1]) + i;
		error = pthread_create(&thread_pid[i], NULL, &sleeper, sleep_time);
		if (error)
			return (perror("pthread"), 1);
		printf("Created sleeper for %d seconds\n", *sleep_time);
	}
	pthread_join(thread_pid[0], NULL);
	pthread_join(thread_pid[1], NULL);
	return (0);
}
