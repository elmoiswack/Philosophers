/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:49:55 by dhussain          #+#    #+#             */
/*   Updated: 2023/04/12 14:43:28 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>
#include <unistd.h>

int	my_strlenght(char *str)
{
	int	index;

	index = 0;
	while (str[index])
		index++;
	return (index);
}

char	*my_strcpy(char *dest, const char *src)
{
	int	index;

	index = 0;
	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}

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
		numb = str[index] - '0';
		sum = sum + numb;
		if (str[index + 1] != '\0')
			sum = sum * 10;
		index++;
	}
	return (sum);
}