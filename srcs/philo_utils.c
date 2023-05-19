/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:54:56 by dhussain          #+#    #+#             */
/*   Updated: 2023/05/19 16:50:07 by dhussain         ###   ########.fr       */
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
	(void)philo;
	
	usleep(time / 3);
	wait_time = get_time() + time;
	while (wait_time >= get_time())
	{
		usleep(250);
	}
	return ;
}

void	fork_initialize(t_philostatus *philo, int index)
{
	philo->left_fork = &(philo->mainstruct->forks[index]);
	if ((index + 1) == philo->mainstruct->number_of_philo)
		philo->right_fork = &(philo->mainstruct->forks[0]);
	else
		philo->right_fork = &(philo->mainstruct->forks[index + 1]);
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
	pthread_mutex_destroy(&philo->mainstruct->mutex_eating_lock);
	pthread_mutex_destroy(&philo->mainstruct->mutex_sleeping_lock);
	pthread_mutex_destroy(&philo->mainstruct->mutex_thinking_lock);
	pthread_mutex_destroy(&philo->mainstruct->mutex_death_lock);
	pthread_mutex_destroy(philo->left_fork);
	pthread_mutex_destroy(philo->right_fork);
	return ;
}