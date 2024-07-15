/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:32:49 by mmeier            #+#    #+#             */
/*   Updated: 2024/06/20 12:17:35 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Returns error 1 in case a char in the string is not a digit*/
static int	not_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

/*Iterates through argument array and passes strings to not_digit function
  in order to check if each string in the array consists only of numbers.*/
static int	ft_nbr_check(char **arr)
{
	int	j;

	j = 1;
	while (arr[j])
	{
		if (not_digit(arr[j]))
			return (1);
		j++;
	}
	return (0);
}

/*Checks if first 4 numbers given to program are smaller or equal 0. 
  In case the optional 5th number is given to program, it is checked,
  whether this number is smaller than 0.*/
static int	check_valid_nbr(int ac, char **arr)
{
	int	nbr1;
	int	nbr2;
	int	nbr3;
	int	nbr4;
	int	nbr5;

	nbr1 = ft_atoi(arr[1]);
	nbr2 = ft_atoi(arr[2]);
	nbr3 = ft_atoi(arr[3]);
	nbr4 = ft_atoi(arr[4]);
	nbr5 = 0;
	if (nbr1 <= 0 || nbr2 <= 0 || nbr3 <= 0 || nbr4 <= 0)
		return (1);
	if (ac == 6)
	{
		nbr5 = ft_atoi(arr[5]);
		if (nbr5 < 0)
			return (1);
	}
	return (0);
}

/*Checks for invalid input, that is, the arguments given are anything else than
  digits and hold certain values (first 4 nbrs are less or equal 0).*/
int	ft_input_check(int ac, char **arr)
{
	if (ft_nbr_check(arr))
		return (1);
	if (check_valid_nbr(ac, arr))
		return (1);
	return (0);
}

int	ft_input_error_msg(int err_no)
{
	if (err_no == 0)
	{
		printf("Error.\nIncorrect amount of arguments.\n");
		return (1);
	}
	if (err_no == 1)
	{
		printf("Error.\nInvalid argument passed to program.\n");
		return (1);
	}
	return (0);
}
