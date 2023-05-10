/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:54:56 by dhussain          #+#    #+#             */
/*   Updated: 2023/05/10 16:45:42 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

long	get_time(void)
{
	struct timeval	current_time;
	long			c_time;

	if (gettimeofday(&current_time, NULL) == -1)
		return (-1);
	c_time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (c_time);
}

void	sleeptight_function(t_philostatus *philo, long time)
{
	long	wait_time;

	wait_time = get_time() - philo->start_time;
	while (wait_time < time)
	{
		wait_time = get_time() - philo->start_time;
		usleep(200);
	}
	return ;
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