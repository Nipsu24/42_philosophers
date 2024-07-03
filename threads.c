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
	pthread_mutex_lock(philo->l_fork);
	print_message(philo, "has taken a fork\n");
	if (philo->table->nbr_of_philos == 1)
	{
		ft_usleep(philo->table->time_to_die);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	print_message(philo, "has taken a fork\n");
	print_message(philo, "is eating\n");
	philo->eating = 1;
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_lock(&philo->table->meal_lock);
	philo->last_time_eaten = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->meal_lock);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

/*usleep * 1000 as input should be in milliseconds (input of this function 
  takes input in microseconds)*/
static void	sleeping(t_philo *philo)
{
	print_message(philo, "is sleeping\n");
	ft_usleep(philo->table->time_to_sleep);
}

static void	thinking(t_philo *philo)
{
	print_message(philo, "is thinking\n");
}

static void	*philo_routine(void *placeholder)
{
	t_philo	*philo;

	philo = (t_philo *)placeholder;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (philo->table->dead_flag == 0)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (placeholder);
}

int	init_threads(t_table *table)
{
	pthread_t	supervisor;
	int			i;

	i = 0;
	if (pthread_create(&supervisor, NULL, control_routine, table) != 0)
		return (1);
	while (i < table->nbr_of_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL,
				philo_routine, &table->philos[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	if (pthread_join(supervisor, NULL) != 0)
		return (1);
	while (i < table->nbr_of_philos)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
