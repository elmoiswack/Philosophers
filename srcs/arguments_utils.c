/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:49:55 by dhussain          #+#    #+#             */
/*   Updated: 2023/04/18 15:40:16 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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

void	*my_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;
	size_t	total;

	total = count * size;
	ptr = (void *) malloc(total);
	if (!ptr)
		return (NULL);
	i = 0;
	while (total > 0)
	{
		ptr[i] = '\0';
		i++;
		total--;
	}
	return ((void *)ptr);
}