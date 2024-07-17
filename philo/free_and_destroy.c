/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:19:44 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/07/17 10:13:48 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_and_error(t_table *table)
{
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
	printf("Error.\nMalloc for structs failed.\n");
	return (1);
}

int	destroy_forks(t_table *table, int i)
{
	while (i > 0)
	{
		pthread_mutex_destroy(&table->forks[i - 1]);
		i--;
	}
	return (1);
}

/*Locks dead_lock mutex and checks status of dead_flag, returns 0 or 1
  depending on dead_flag status*/
int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->dead_lock);
	if (philo->table->dead_flag != 1)
	{
		pthread_mutex_unlock(&philo->table->dead_lock);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&philo->table->dead_lock);
		return (1);
	}	
}

/*Locks print_lock mutex and prints required values, given
  a philosopher is not dead yet*/
void	print_message(t_philo *philo, char *str)
{
	size_t	cur_time;

	pthread_mutex_lock(&philo->table->print_lock);
	cur_time = get_time() - philo->table->start_sim;
	if (!is_dead(philo))
		printf("%zu %d %s", cur_time, philo->id, str);
	pthread_mutex_unlock(&philo->table->print_lock);
}

/*Destroys mutexes and frees allocated memory (order is important
  regarding fork mutexes- first destroy, then free memory)*/
void	destroy_and_free(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_of_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
	free(table->philos);
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->meal_lock);
	pthread_mutex_destroy(&table->dead_lock);
}
