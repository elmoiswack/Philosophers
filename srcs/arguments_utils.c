/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:49:55 by dhussain          #+#    #+#             */
/*   Updated: 2023/04/06 11:03:42 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>
#include <unistd.h>

int	my_is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (-1);
}

int	my_atoi(char *str)
{
	int	index;
	int	numb;
	int	sum;

	index = 0;
	sum = 0;
	if (str[0] == '-')
		return (-1);
	while (str[index])
	{
		if (my_is_digit(str[index]) == -1)
			return (-1);
		numb = str[index] - '0';
		sum = sum + numb;
		if (str[index + 1] != '\0')
			sum = sum * 10;
		index++;
	}
	return (sum);
}