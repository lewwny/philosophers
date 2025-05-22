/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:17:58 by lengarci          #+#    #+#             */
/*   Updated: 2025/05/22 18:57:38 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_philo	philo;

	memset(&philo, 0, sizeof(t_philo));
	if (!test_args(argv, argc, &philo))
		return (1);
	init_args(&philo, argv);
	return (0);
}
