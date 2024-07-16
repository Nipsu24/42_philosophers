/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:43:51 by mmeier            #+#    #+#             */
/*   Updated: 2024/07/16 10:19:09 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Checks if all philos ate the sufficient amount of meals. If
  this is the case, sets dead_flag to 1 in order to end
  simulation.*/
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
		pthread_mutex_lock(&table->meal_lock);
		if (table->philos[i].meals_eaten >= table->meals_to_eat)
			all_ate++;
		pthread_mutex_unlock(&table->meal_lock);
		i++;
	}
	if (all_ate == table->nbr_of_philos)
	{
		pthread_mutex_lock(&table->dead_lock);
		table->dead_flag = 1;
		pthread_mutex_unlock(&table->dead_lock);
		return (1);
	}
	return (0);
}

/*Helper function of philo_died function, returns 0 in case
  philo has not managed to eat in time.*/
static int	eaten_in_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->meal_lock);
	if ((get_time() - philo->last_time_eaten >= philo->table->time_to_die)
		&& philo->eating == 0)
	{
		pthread_mutex_unlock(&philo->table->meal_lock);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&philo->table->meal_lock);
		return (1);
	}
}

/*Checks if philo has eaten in time and if not, sets dead_flag to 1
  after locking value with dedicated mutex.*/
static int	philo_died(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_of_philos)
	{
		if (!eaten_in_time(&table->philos[i]))
		{
			print_message(&table->philos[i], "died\n");
			pthread_mutex_lock(&table->dead_lock);
			table->dead_flag = 1;
			pthread_mutex_unlock(&table->dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

/*Main control_routine function with sub-routines which check whether
  all philos have eaten their meals or any has died*/
void	*control_routine(void *placeholder)
{
	t_table	*table;

	table = (t_table *)placeholder;
	while (1)
	{
		if (meal_over(table) || philo_died(table))
			break ;
	}
	return (placeholder);
}
