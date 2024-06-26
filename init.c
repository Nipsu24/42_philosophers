/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:21:37 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/06/26 14:58:39 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_table(t_table *table, t_philo *philos, char **av)
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
	table->philos = philos;
	table->dead_flag = 0;

	printf("nbr of philos: %d\n", table->nbr_of_philos);
	printf("time_to_die: %d\n", table->time_to_die);
	printf("time_to_eat: %d\n", table->time_to_eat);
	printf("time_to_sleep: %d\n", table->time_to_sleep);
	printf("meals_to eat: %d\n", table->meals_to_eat);
	printf("start_sim: %zu\n", table->start_sim);
}

/*Initialises pthread_mutex_t for each element 'i' in the forks array. Therefore
  address of each i (&forks[i]) need to be passed to init function and not only 
  forks[i]*/
static void	init_forks(pthread_mutex_t *forks, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

static void	init_philo(t_philo *philo, t_table *table, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < table->nbr_of_philos)
	{
		philo[i].id = i + 1;
		philo[i].last_time_eaten = 0;
		philo[i].meals_eaten = 0;
		philo[i].eating = 0;
		philo[i].l_fork = &forks[i];
		if (i == 0)
			philo[i].r_fork = &forks[table->nbr_of_philos - 1];
		else
			philo[i].r_fork = &forks[i - 1];
		philo[i].table = table;
		philo[i].dead = table->dead_flag;
		printf("philo ID: %d\n", philo[i].id);
		printf("last_time_eaten: %zu\n", philo[i].last_time_eaten);
		i++;
	}
}

void	init_structs(t_table *table, t_philo *philos,
						pthread_mutex_t *forks, char **av)
{
	init_table(table, philos, av);
	init_forks(forks, table);
	init_philo(philos, table, forks);
}
