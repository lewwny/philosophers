/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:44:46 by lengarci          #+#    #+#             */
/*   Updated: 2025/06/11 15:45:58 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	thread_create(t_philo *philosophers, t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < data->numbers_philo)
	{
		if (pthread_create(&philosophers[i].thread,
				NULL, routine, &philosophers[i]) != 0)
			return ;
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitoring, philosophers) != 0)
		return ;
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < data->numbers_philo)
		pthread_join(philosophers[i++].thread, NULL);
}

static void	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->numbers_philo);
	if (!data->forks)
		return ;
	i = 0;
	while (i < data->numbers_philo)
		pthread_mutex_init(&data->forks[i++], NULL);
}

static void	init_philo_structs(t_philo *philosophers,
	t_data *data, pthread_t *thread)
{
	int	i;

	i = 0;
	while (i < data->numbers_philo)
	{
		philosophers[i].id = i + 1;
		philosophers[i].data = data;
		philosophers[i].last_meal_time = data->start_time;
		philosophers[i].left_fork = &data->forks[i];
		philosophers[i].right_fork = &data->forks[(i + 1)
			% data->numbers_philo];
		philosophers[i].thread = thread[i];
		philosophers[i].number_of_eat = 0;
		i++;
	}
}

void	init_philos(t_data *data)
{
	t_philo		*philosophers;
	pthread_t	*thread;
	int			i;

	philosophers = malloc(sizeof(t_philo) * data->numbers_philo);
	if (!philosophers)
		return ;
	thread = malloc(sizeof(pthread_t) * data->numbers_philo);
	if (!thread)
		return ;
	init_forks(data);
	if (!data->forks)
		return ;
	init_philo_structs(philosophers, data, thread);
	thread_create(philosophers, data);
	i = 0;
	while (i < data->numbers_philo)
		pthread_mutex_destroy(&data->forks[i++]);
	free(data->forks);
	free(philosophers);
	free(thread);
}
