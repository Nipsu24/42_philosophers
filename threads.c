/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:15:29 by mmeier            #+#    #+#             */
/*   Updated: 2024/06/27 15:09:44 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philo *philo)
{
	size_t	cur_time;
	
	pthread_mutex_lock(philo->l_fork);
	cur_time = get_time() - philo->table->start_sim;
	printf("%zu %d has taken a fork\n", cur_time, philo->id);
	pthread_mutex_lock(philo->r_fork);
	cur_time = get_time() - philo->table->start_sim;
	printf("%zu %d has taken a fork\n", cur_time, philo->id);
	cur_time = get_time() - philo->table->start_sim;
	printf("%zu %d is eating\n", cur_time, philo->id);
	philo->eating = 1;
	usleep(philo->table->time_to_eat * 1000);
	philo->last_time_eaten = get_time() - philo->table->start_sim;
	philo->meals_eaten++;
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

/*usleep * 1000 as input should be in milliseconds (input of this function 
  takes input in microseconds)*/
static void	sleeping(t_philo *philo)
{
	size_t	cur_time;

	cur_time = get_time() - philo->table->start_sim;
	printf("%zu %d is sleeping\n", cur_time, philo->id);
	usleep(philo->table->time_to_sleep * 1000);
}

static void	thinking(t_philo *philo)
{
	size_t	cur_time;

	cur_time = get_time() - philo->table->start_sim;
	printf("%zu %d is thinking\n", cur_time, philo->id);
}

static void	*philo_routine(void *placeholder)
{
	t_philo	*philo;

	philo = (t_philo *)placeholder;
	if (philo->id % 2 == 0)
		usleep(500);
	while (philo->table->dead_flag == 0)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (placeholder);
}

int	init_threads(t_philo *philo, t_table *table)
{
	pthread_t	supervisor;
	int			i;

	i = 0;
	if (pthread_create(&supervisor, NULL, control_routine, table) != 0)
		return (1);
	while (i < table->nbr_of_philos)
	{
		if (pthread_create(&philo[i].thread, NULL,
				philo_routine, &table->philos[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	if (pthread_join(supervisor, NULL) != 0)
		return (1);
	while (i < table->nbr_of_philos)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
