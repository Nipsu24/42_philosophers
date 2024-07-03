/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:43:51 by mmeier            #+#    #+#             */
/*   Updated: 2024/06/27 15:10:47 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	meal_over(t_table *table)
{
	int	i;
	int	all_ate;
	
	i = 0;
	all_ate = 0;
	if (table->meals_to_eat == -1)
		return (0);
	while (i < table->nbr_of_philos)
	{
		if (table->philos[i].meals_eaten >= table->meals_to_eat)
			all_ate++;
		i++;
	}
	if (all_ate == table->nbr_of_philos)
	{
		table->dead_flag = 1;
		return (1);
	}
	return (0);
}

static int	philo_died(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_of_philos)
	{
		//pthread_mutex_lock(&table->meal_lock);
		if (table->philos[i].eating == 0)
		{
			if (get_time() - table->philos[i].last_time_eaten >= table->time_to_die)
			{
				//pthread_mutex_unlock(&table->meal_lock);
				print_message(&table->philos[i], "died\n");
				table->dead_flag = 1;
				return (1);
			}
			// else
			// 	pthread_mutex_unlock(&table->meal_lock);
		}
		i++;
	}
	return (0);
}

void	*control_routine(void *placeholder)
{
	t_table	*table;
	
	table = (t_table *)placeholder;
	while (1)
	{
		if (meal_over(table) || philo_died(table))
			break;
	}
	return (placeholder);
}
