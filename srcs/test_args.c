/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:20:28 by lengarci          #+#    #+#             */
/*   Updated: 2025/05/22 18:28:36 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	ft_puterror(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(2, str, i);
}

static int	test_count_args(int argc)
{
	if (argc < 5 || argc > 6)
	{
		ft_puterror("Error\nUse ./philosophers number_of_philosophers ");
		ft_puterror("time_to_die time_to_eat time_to_sleap ");
		ft_puterror("[number_of_times_each_philosophers_must_eat]\n");
		return (0);
	}
	return (1);
}

static int	test_argv(char *str)
{
	int	i;
	int	count;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		count++;
		i++;
	}
	if (str[i] || !count)
		return (0);
	return (1);
}

int	test_args(char **argv, int argc, t_philo *philo)
{
	int	i;

	i = 0;
	if (!test_count_args(argc))
		return (0);
	while (argv[i])
	{
		if (!test_argv(argv[i]))
			return (0);
		i++;
	}
	if (argc == 6)
		philo->last_param = 1;
	else
		philo->last_param = 0;
	return (1);
}
