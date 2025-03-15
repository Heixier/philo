/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:08:46 by rsiah             #+#    #+#             */
/*   Updated: 2025/02/21 12:32:52 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

typedef struct s_data
{
	pthread_t	id;
	char		*name;
}				t_data;


void	*thread_test(void *data)
{
	t_data	*p_data;
	p_data = (t_data *)data;

	printf("Name of thread is %s\n", p_data -> name);
	free(p_data);
	return (NULL);
}

void	create_thread(char *name)
{
	pthread_t	output;
	t_data		*p_data;

	p_data = calloc(sizeof(p_data), 1);
	p_data -> name = name;
	pthread_create(&output, NULL, thread_test, p_data);
	pthread_join(output, NULL);
}

int	main(int argc, char **argv)
{
	for (int i = 1; i < argc; i++)
		create_thread(argv[i]);
}
