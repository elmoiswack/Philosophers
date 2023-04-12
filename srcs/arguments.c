/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:33:55 by dhussain          #+#    #+#             */
/*   Updated: 2023/04/12 14:45:35 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	overflow_check(char *argv[])
{
	int		index;
	char 	*str;
	
	index = 1;
	if (my_strlenght(argv[index]) > 10)
		return (-1);
	if (my_strlenght(argv[index] < 10))
		return (1);
	str = malloc(11 * sizeof(char));
	if (!str)
		return (-1);
	my_strcpy(str, "2147483647");
	while (argv[index])
	{
		if (argv[index] > str[index])
			return (-1);
		index++;
	}
	free(str);
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
	if (overflow_check(argv) == -1)
		return (-1);
	return (1);
}

int	filling_struct(char *argv[], t_mainstruct *m_struct)
{
	m_struct->number_philo = my_atoi(argv[1]);
	return (1);
	
}