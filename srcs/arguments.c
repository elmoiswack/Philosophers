/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:33:55 by dhussain          #+#    #+#             */
/*   Updated: 2023/04/05 13:47:00 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	digit_checker(char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] >= '0' && str[index] <= '9')
			index++;
		else
			return (-1);
	}
	return (1);
}

int	argv_checker(char *argv[])
{
	int	index;
	
	index = 1;
	while (argv[index])
	{
		if (digit_checker(argv[index]) == -1)
			return (-1);
		index++;
	}
	return (1);
}

int	arg_checker(int argc, char *argv[])
{
	if (argc < 5)
		return (-1);
	if (argc > 5)
		return (-1);
	if (argv_checker(argv) == -1)
		return (-1);
	return (1);
}