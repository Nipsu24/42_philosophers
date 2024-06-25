/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariusmeier <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:21:37 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/06/24 12:21:40 by mariusmeier      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(t_table *table, char **av)
{
	{
		table->nbr_of_philos = ft_atoi(av[1]);
		table->time_to_die = ft_atoi(av[2]);
		table->time_to_eat = ft_atoi(av[3]);
		table->time_to_sleep = ft_atoi(av[4]);
		if (av[5])
			table->meals_to_eat = ft_atoi(av[5]);
		else
			table->meals_to_eat = -1;
	}
}
void	init_philo(t_philo *philo, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philo->id = i + 1;
		philo->last_time_eaten = 0;
		i++;
	}
}
