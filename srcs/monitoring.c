/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:35:13 by lengarci          #+#    #+#             */
/*   Updated: 2025/06/11 14:41:50 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*monitoring(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	int	i;

	philo = (t_philo *)arg;
	data = philo[0].data;
	while (1)
	{
		i = 0;
		while (i < data->numbers_philo)
		{
			if (get_time_ms() - philo[i].last_meal_time > data->time_to_die)
			{
				data->is_dead = true;
				print_dead(&philo[i]);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}