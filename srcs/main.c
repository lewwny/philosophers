/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:17:58 by lengarci          #+#    #+#             */
/*   Updated: 2025/06/11 15:11:33 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	handle_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	usleep(philo->data->time_to_die * 1000);
	pthread_mutex_unlock(philo->left_fork);
}

static void	philo_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
	print_action(philo, "is eating");
	philo->last_meal_time = get_time_ms();
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->numbers_philo == 1)
	{
		handle_one_philo(philo);
		return (NULL);
	}
	while (1)
	{
		if (philo->data->is_dead)
			return (NULL);
		philo_eat(philo);
		print_action(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		print_action(philo, "is thinking");
	}
	return (NULL);
}

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

static void	init_philo_structs(t_philo *philosophers, t_data *data, pthread_t *thread)
{
	int	i;

	i = 0;
	while (i < data->numbers_philo)
	{
		philosophers[i].id = i + 1;
		philosophers[i].data = data;
		philosophers[i].last_meal_time = data->start_time;
		philosophers[i].left_fork = &data->forks[i];
		philosophers[i].right_fork = &data->forks[(i + 1) % data->numbers_philo];
		philosophers[i].thread = thread[i];
		i++;
	}
}

static void	init_philos(t_data *data)
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

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (!test_args(argv, argc, &data))
		return (1);
	init_args(&data, argv);
	data.start_time = get_time_ms();
	init_philos(&data);
	pthread_mutex_destroy(&data.print_lock);
	return (0);
}
