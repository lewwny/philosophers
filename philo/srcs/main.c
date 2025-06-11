/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:17:58 by lengarci          #+#    #+#             */
/*   Updated: 2025/06/11 17:00:18 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
	pthread_mutex_destroy(&data.state_lock);
	return (0);
}
