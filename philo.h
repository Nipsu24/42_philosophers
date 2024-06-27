/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:39:08 by mmeier            #+#    #+#             */
/*   Updated: 2024/06/27 15:08:24 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define PHILO_MAX 250
/*Struct containing all relevant data of a philosopher*/
typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				id;
	int				eating;
	int				meals_eaten;
	int				*dead;
	size_t			last_time_eaten;
	struct s_table	*table;
}				t_philo;

/*Struct containing all relevant data of the table (shared data of philos)*/
typedef struct s_table
{
	int		nbr_of_philos;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int		meals_to_eat;
	int		dead_flag;
	size_t	start_sim;
	t_philo	*philos;
}				t_table;

int		ft_isdigit(int n);
int		ft_atoi(const char *str);
int		ft_input_error_msg(int err_no);
int		ft_input_check(int ac, char **arr);
void	init_structs(t_table *table, t_philo *philos,
			pthread_mutex_t *forks, char **av);
int		init_threads(t_philo *philo, t_table *table);
size_t	get_time(void);
void	*control_routine(void *placeholder);

#endif