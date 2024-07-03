/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 09:58:42 by mmeier            #+#    #+#             */
/*   Updated: 2024/06/26 12:13:15 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_table			table;
	
	if (ac < 5 || ac > 6)
		return (ft_input_error_msg(0));
	if (ft_input_check(ac, av))
		return (ft_input_error_msg(1));
	printf("Correct Input received\n");
	if (init_structs(&table, av))
		return (free_and_error(&table));
	init_threads(&table);
	destroy_and_free(&table);
	return (0);
}
