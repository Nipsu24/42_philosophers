/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariusmeier <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:19:44 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/06/28 11:19:46 by mariusmeier      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_and_error(t_table *table)
{
	if (table->forks)
	{
		free(table->forks);
		printf("Error.\nMalloc for structs failed.\n");
		return (1);
	}
	return (0);
}
void	ft_usleep(size_t ms)
{
	size_t	start;
	
	start = get_time();
	while ((get_time() - start) < ms)
		usleep(500);
}

void	print_message(t_philo *philo, char *str)
{
	size_t	cur_time;

	pthread_mutex_lock(philo->print);
	cur_time = get_time() - philo->table->start_sim;
	if (philo->table->dead_flag != 1)
		printf("%zu %d %s", cur_time, philo->id, str);
	pthread_mutex_unlock(philo->print);
}
void	destroy_and_free(t_table *table)
{
	int	i;

	i = 0;
	free(table->forks);
	free(table->philos);
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->meal_lock);
	while (i < table->nbr_of_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
}
