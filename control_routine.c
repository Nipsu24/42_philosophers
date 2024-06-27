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
	size_t	cur_time;

	i = 0;
	cur_time = 0;
	while (i < table->nbr_of_philos)
	{
		if (table->philos[i].eating == 0)
		{
			cur_time = get_time() - table->start_sim;
			if (table->philos[i].last_time_eaten - cur_time > table->time_to_die)
			{
				printf("%zu %d died\n", cur_time, table->philos[i].id);
				table->dead_flag = 1;
				return (1);
			}
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
