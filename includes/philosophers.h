/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:11:42 by lengarci          #+#    #+#             */
/*   Updated: 2025/05/22 18:31:35 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/wait.h>
# include <stdbool.h>

typedef struct s_philo
{
	int		numbers_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_eat;
	bool	last_param;
}	t_philo;

int	test_args(char **argv, int argc, t_philo *philo);
void	init_args(t_philo *philo, char **argv);

#endif
