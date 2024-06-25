/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:15:29 by mmeier            #+#    #+#             */
/*   Updated: 2024/06/25 16:32:44 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	sleeping(t_table *table)
{
	usleep(300);
	//usleep(table->time_to_sleep);
	printf("%zu %d is sleeping\n", table->start_sim, table->philos->id);
}

static void	thinking(t_table *table)
{
	printf("%zu %d is thinking\n", table->start_sim, table->philos->id);
}

static void	*philo_routine(void *placeholder)
{
	t_table *table;
	
	table = (t_table *)placeholder;
	while (1)
	{
		//eat
		printf("TEST2\n");
		sleeping(table);
		thinking(table);
	}
	return (0);
}

int	thread_create(t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_of_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, philo_routine, &table->philos[i])!= 0)
			return (1);
		//printf("TEST\n");
		i++;
	}
	return (0);
}
