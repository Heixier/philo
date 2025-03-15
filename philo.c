/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 23:18:17 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/06 23:23:17 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*cat_eat(void *args)
{
	t_cat	*cat;
	
	cat = (t_cat *)args;
	while (1)
	{
		pthread_mutex_lock(&cat -> data -> food);
		if (cat -> data -> cat_died)
			return (pthread_mutex_unlock(&cat -> data -> food), NULL);
		printf("Cat %d grabbed the food\n", cat -> id);
		if (cat -> data -> food_left < cat -> data -> amt_to_eat)
			return (pthread_mutex_unlock(&cat -> data -> food), NULL);
		sleep(cat -> data -> amt_to_eat);
		cat -> times_eaten++;
		cat -> data -> food_left -= cat -> data -> amt_to_eat;
		printf("Cat %d is resting... food left: %d\n", cat -> id, cat -> data -> food_left);
		pthread_mutex_unlock(&cat -> data -> food);
		cat -> time_before_death = cat -> data -> hunger;
		usleep(1000);
	}
	return (NULL);
}

void	*kill_cats(void *args)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)args;
	while (1)
	{
		i = i % data -> num_cats;
		if (data -> cats[i] -> time_before_death > 0)
		{
			printf("cat %d time before death: %d\n", i, data -> cats[i] -> time_before_death);
			data -> cats[i] -> time_before_death--;
		}
		if (data -> cats[i] -> time_before_death <= 0)
		{
			printf("cat %d died\n", i);
			data -> cat_died = 1;
			return (NULL);
		}
		usleep(1000);
		i++;
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	t_data			*data;
	int				num_cats;
	pthread_t		*cat_threads;
	pthread_t		cat_manager;

	if (argc > 1)
		num_cats = atoi(argv[1]);
	else
		num_cats = 1;
	cat_threads = calloc(sizeof(pthread_t), num_cats);

	data = calloc(sizeof(t_data), 1);
	pthread_mutex_init(&data -> food, NULL);
	data -> cats = calloc(sizeof(t_cat *), num_cats);
	data -> num_cats = num_cats;

	if (argc > 2)
		data -> food_left = atoi(argv[2]);
	else
		data -> food_left = 10;
	if (argc > 3)
		data -> amt_to_eat = atoi(argv[3]);
	else
		data -> amt_to_eat = 5;
	if (argc > 4)
		data -> hunger = atoi(argv[4]);
	else
		data -> hunger = 100;

	for (int i = 0; i < num_cats; i++)
	{
		data -> cats[i] = calloc(sizeof(t_cat), 1);
		data -> cats[i] -> id = i;
		data -> cats[i] -> data = data;
		data -> cats[i] -> time_before_death = data -> hunger;
		pthread_create(&cat_threads[i], NULL, cat_eat, data -> cats[i]);
	}
	

	// cat manager
	pthread_create(&cat_manager, NULL, kill_cats, data);

	printf("Number of cats: %d\nAmount to eat: %d\nAmount of food: %d\n", num_cats, data -> amt_to_eat, data -> food_left);



	for (int i = 0; i < num_cats; i++)
		pthread_join(cat_threads[i], NULL);
	pthread_join(cat_manager, NULL);
	for (int i = 0; i < num_cats; i++)
	{
		printf("Cat %d: Times eaten: %d\n", i, data -> cats[i] -> times_eaten);
		free(data -> cats[i]);
	}
	free(data -> cats);
	free(data);
	free(cat_threads);
}
