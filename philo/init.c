/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:21:37 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/07/16 11:49:24 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Initialises table struct, destroys previous initialised mutexes straight 
  away in case error occurs with current mutex init*/
static int	init_table(t_table *table, char **av)
{
	table->nbr_of_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		table->meals_to_eat = ft_atoi(av[5]);
	else
		table->meals_to_eat = -1;
	table->start_sim = get_time();
	table->dead_flag = 0;
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->meal_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&table->print_lock);
		return (1);
	}
	if (pthread_mutex_init(&table->dead_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&table->print_lock);
		pthread_mutex_destroy(&table->meal_lock);
		return (1);
	}
	return (0);
}

/*Allocates sufficient amount of memory for array of philo-structs and
  array of fork mutexes*/
static int	init_mem_philo_forks(t_table *table)
{
	table->philos = malloc(sizeof(t_philo) * table->nbr_of_philos);
	if (!table->philos)
		return (1);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr_of_philos);
	if (!table->forks)
		return (1);
	return (0);
}

/*Initialises mutex for each element 'i' in the forks mutex array. In case
  of error, destroys initialised mutexes with destroy_forks function.*/
static int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_of_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			return (destroy_forks(table, i));
		}
		i++;
	}
	return (0);
}

/*Initialise all philo structs (amount depending on first argument
  given to program). The 1st philosopher (philo[0]) gets assigned
  as the right fork the fork of the last philo (philos sit in circle
  around table). Function could also be void but int needed for 
  init_structs function definition (int not void)*/
static int	init_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_of_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].last_time_eaten = get_time();
		table->philos[i].meals_eaten = 0;
		table->philos[i].l_fork = &table->forks[i];
		if (i == 0)
			table->philos[i].r_fork = &table->forks[table->nbr_of_philos - 1];
		else
			table->philos[i].r_fork = &table->forks[i - 1];
		table->philos[i].table = table;
		i++;
	}
	return (0);
}

int	init_structs(t_table *table, char **av)
{
	if (init_table(table, av))
		return (1);
	if (init_mem_philo_forks(table))
		return (1);
	if (init_forks(table))
		return (1);
	if (init_philo(table))
		return (1);
	return (0);
}
