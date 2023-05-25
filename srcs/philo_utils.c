/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantehussain <dantehussain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:54:56 by dhussain          #+#    #+#             */
/*   Updated: 2023/05/25 23:45:22 by dantehussai      ###   ########.fr       */
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

void	sleeptight_function(long time)
{
	long	wait_time;

	usleep(time / 3);
	wait_time = get_time() + time;
	while (wait_time >= get_time())
		usleep(250);
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
	return ;
}

int	printing_action(t_philostatus *philo, int philo_id, const char *str)
{
	long	time;

	pthread_mutex_lock(&philo->mainstruct->printing_lock);
	time = get_time();
	if (time == -1)
	{
		pthread_mutex_unlock(&philo->mainstruct->printing_lock);
		return (-1);
	}
	time -= philo->mainstruct->start_time;
	if (philo->mainstruct->someone_died != 1 && philo->mainstruct->everyone_is_full != 1)
		printf("%lu %i %s\n", time, philo_id, str);
	pthread_mutex_unlock(&philo->mainstruct->printing_lock);
	return (1);
}