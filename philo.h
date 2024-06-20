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

/*Struct containing command structure extracted from tokens*/
// typedef struct s_command
// {
// 	char				*cnt;
// }				t_command;

int	ft_isdigit(int n);
int	ft_atoi(const char *str);
int	ft_input_error_msg(int err_no);
int	ft_input_check(int ac, char **arr);

#endif