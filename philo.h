/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:39:08 by mmeier            #+#    #+#             */
/*   Updated: 2024/06/20 10:59:45 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>

# define PHILO_MAX 250
/*Struct containing all relevant data of a philosopher*/
typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t *r_fork;
	int				id;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				last_time_eaten;
}				t_philo;

typedef struct s_table
{
	t_philo		philos;
}				t_table;

int	ft_isdigit(int n);
int	ft_atoi(const char *str);
int	ft_input_error_msg(int err_no);
int	ft_input_check(int ac, char **arr);

#endif