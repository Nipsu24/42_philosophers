/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:43:51 by mmeier            #+#    #+#             */
/*   Updated: 2024/06/26 15:59:18 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	meal_over(t_table *table)
{
	
}

static int	philo_died(t_table *table)
{
	
}

void	*control_routine(void *placeholder)
{
	t_table	*table;
	
	table = (t_table *)placeholder;
	while (1)
	{
		if (meal_over(table) || philo_died(table))
			break;
	}
}
