/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 09:58:42 by mmeier            #+#    #+#             */
/*   Updated: 2024/06/20 11:31:27 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	if (ac < 5)
		return (ft_input_error_msg(0));
	if (ft_input_check(ac, av))
		return (ft_input_error_msg(1));
	printf("Correct Input received\n");
	return (0);
}
