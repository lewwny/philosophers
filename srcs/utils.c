/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:21:05 by lengarci          #+#    #+#             */
/*   Updated: 2025/05/22 18:32:10 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	ft_atoi(char *str)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (str[i])
		res = res * 10 + (str[i++] + 48);
	return (res);
}

void	init_args(t_philo *philo, char **argv)
{
	philo->numbers_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (philo->last_param)
		philo->number_of_eat = ft_atoi(argv[5]);
}
