/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantehussain <dantehussain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:33:55 by dhussain          #+#    #+#             */
/*   Updated: 2023/05/25 21:28:17 by dantehussai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdlib.h>
#include <stdio.h>

int	digit_checker(char *str)
{
	int	index;

	index = 0;
	if (str[0] == '\0')
		return (-1);
	if (str[0] == '-')
		return (-1);
	if (str[0] == '0')
		return (-1);
	while (str[index])
	{
		if (str[index] >= '0' && str[index] <= '9')
			index++;
		else
			return (-1);
	}
	return (1);
}

int	overflow_check(char *arg_str)
{
	int		index;
	char 	*str;
	
	index = 1;
	if (my_strlenght(arg_str) > 10)
		return (-1);
	if (my_strlenght(arg_str) < 10)
		return (1);
	str = malloc(11 * sizeof(char));
	if (!str)
		return (-1);
	my_strcpy(str, "2147483647");
	while (arg_str[index])
	{
		if (arg_str[index] > str[index])
		{
			free(str);
			return (-1);
		}
		index++;
	}
	free(str);
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
		if (overflow_check(argv[index]) == -1)
			return (-1);
		index++;
	}
	return (1);
}

int	arg_checker(int argc, char *argv[])
{
	if (argc < 5)
		return (-1);
	if (argc > 6)
		return (-1);
	if (argv_checker(argv) == -1)
		return (-1);
	return (1);
}

int	filling_struct(char *argv[], t_mainstruct *m_struct)
{
	m_struct->number_of_philo = my_atoi(argv[1]);
	m_struct->time_to_die = my_atoi(argv[2]);
	m_struct->time_to_eat = my_atoi(argv[3]);
	m_struct->time_to_sleep = my_atoi(argv[4]);
	if (argv[5])
		m_struct->ammount_of_eating = my_atoi(argv[5]);
	else
		m_struct->ammount_of_eating = -1;
	return (1);
}
