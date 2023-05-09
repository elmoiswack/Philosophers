/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:54:56 by dhussain          #+#    #+#             */
/*   Updated: 2023/05/09 13:26:31 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <sys/time.h>
#include <stdio.h>

long	get_time(void)
{
	struct timeval	current_time;
	long			c_time;
	static long		s_time;
	static struct	timeval start_time;
	static int 		check;
	
	if (check == 0)
	{
		gettimeofday(&start_time, NULL);
		s_time = (start_time.tv_sec * 1000) + (start_time.tv_usec / 1000);
		check = 1;
	}
	if (gettimeofday(&current_time, NULL) == -1)
		return (-1);
	c_time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (c_time - s_time);
}

void	finishing_threads(t_philostatus *philo)
{
	int	index;

	index = 0;
	while (index < philo->mainstruct->number_of_threads)
	{
		pthread_join(philo->mainstruct->threads[index], NULL);
		index++;
	}
	pthread_mutex_destroy(&philo->mainstruct->mutex_lock);
}