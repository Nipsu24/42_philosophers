/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:21:37 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/06/27 15:27:58 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_mutex_init(&table->print_lock, NULL);
	pthread_mutex_init(&table->meal_lock, NULL);

	printf("nbr of philos: %d\n", table->nbr_of_philos);
	printf("time_to_die: %ld\n", table->time_to_die);
	printf("time_to_eat: %ld\n", table->time_to_eat);
	printf("time_to_sleep: %ld\n", table->time_to_sleep);
	printf("meals_to eat: %d\n", table->meals_to_eat);
	printf("start_sim: %zu\n", table->start_sim);
	return (0);
}

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

/*Initialises pthread_mutex_t for each element 'i' in the forks array. Therefore
  address of each i (&forks[i]) need to be passed to init function and not only 
  forks[i]*/
static int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_of_philos)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	return (0);
}

static int	init_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_of_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].last_time_eaten = get_time();
		table->philos[i].meals_eaten = 0;
		table->philos[i].eating = 0;
		table->philos[i].l_fork = &table->forks[i];
		if (i == 0)
			table->philos[i].r_fork = &table->forks[table->nbr_of_philos - 1];
		else
			table->philos[i].r_fork = &table->forks[i - 1];
		table->philos[i].table = table;
		table->philos[i].dead = &(table->dead_flag);
		table->philos[i].print = &(table->print_lock);
		printf("philo ID: %d\n", table->philos[i].id);
		printf("last_time_eaten: %zu\n", table->philos[i].last_time_eaten);
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
	if(init_philo(table))
		return (1);
	return (0);
}
