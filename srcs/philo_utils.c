/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:54:56 by dhussain          #+#    #+#             */
/*   Updated: 2023/07/23 14:27:20 by dhussain         ###   ########.fr       */
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

	gettimeofday(&current_time, NULL);
	c_time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (c_time);
}

int	sleeptight_function(long time, t_philostatus *philo)
{
	long	wait_time;
	long	time_loop;

	usleep(time / 3);
	wait_time = get_time() - philo->mainstruct->start_time;
	wait_time += time;
	time_loop = get_time() - philo->mainstruct->start_time;
	while (wait_time >= time_loop)
	{
		if (philo->current_time >= philo->time_must_eat)
		{
			philo->mainstruct->someone_died = 1;
			break ;
		}
		time_loop = get_time() - philo->mainstruct->start_time;
		if (time_loop == -1)
			return (-1);
		usleep(200);
	}
	return (1);
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
	return ;
}

int	printing_action(t_philostatus *philo, int philo_id, const char *str)
{
	long	time;

	pthread_mutex_lock(&philo->mainstruct->printing_lock);
	time = get_time();
	time -= philo->mainstruct->start_time;
	if (philo->mainstruct->someone_died != 1 \
		&& philo->mainstruct->everyone_is_full != 1)
		printf("%lu %i %s\n", time, philo_id, str);
	pthread_mutex_unlock(&philo->mainstruct->printing_lock);
	return (1);
}
