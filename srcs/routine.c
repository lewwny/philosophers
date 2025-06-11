/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:47:00 by lengarci          #+#    #+#             */
/*   Updated: 2025/06/11 16:18:17 by lengarci         ###   ########.fr       */
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

static void	philo_take_forks(t_philo *philo)
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
}

static int	philo_eat(t_philo *philo)
{
	philo_take_forks(philo);
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->data->state_lock);
	philo->number_of_eat++;
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->data->state_lock);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	if (philo->data->last_param && philo->number_of_eat
		>= philo->data->number_of_eat)
		return (0);
	return (1);
}

void	*routine(void *arg)
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
		if (!philo_eat(philo))
			return (NULL);
		print_action(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		print_action(philo, "is thinking");
	}
	return (NULL);
}
