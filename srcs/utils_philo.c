/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:03:15 by lengarci          #+#    #+#             */
/*   Updated: 2025/06/11 14:43:43 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

void	print_action(t_philo *philo, const char *action)
{
	long long	time;

	pthread_mutex_lock(&philo->data->print_lock);
	time = get_time_ms() - philo->data->start_time;
	if (!philo->data->is_dead)
		printf("%lld %d %s\n", time, philo->id, action);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	print_dead(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->data->print_lock);
	time = get_time_ms() - philo->data->start_time;
	printf("%lld %d died\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->print_lock);
}
