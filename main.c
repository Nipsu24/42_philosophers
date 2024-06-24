/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 09:58:42 by mmeier            #+#    #+#             */
/*   Updated: 2024/06/20 12:03:44 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_philo	philos[PHILO_MAX];
	t_table;
	pthread_mutex_t forks[PHILO_MAX];
	
	if (ac < 5 || ac > 6)
		return (ft_input_error_msg(0));
	if (ft_input_check(ac, av))
		return (ft_input_error_msg(1));
	printf("Correct Input received\n");
	return (0);
}
