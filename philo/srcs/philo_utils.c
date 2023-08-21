/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantehussain <dantehussain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:54:56 by dhussain          #+#    #+#             */
/*   Updated: 2023/08/21 05:22:42 by dantehussai      ###   ########.fr       */
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

	usleep((time / 3));
	wait_time = get_time() - philo->mainstruct->start_time;
	wait_time += time;
	time_loop = get_time() - philo->mainstruct->start_time;
	while (wait_time >= time_loop)
	{
		time_loop = get_time() - philo->mainstruct->start_time;
		usleep(200);
	}
	return (1);
}

void	fork_initialize(t_mainstruct *m_struct)
{
	int	index;

	index = 0;
	while (index < m_struct->number_of_philo)
	{
		m_struct->philo_st[index].left_fork = &(m_struct->forks[index]);
		if ((index + 1) == m_struct->number_of_philo)
			m_struct->philo_st[index].right_fork = &(m_struct->forks[0]);
		else
			m_struct->philo_st[index].right_fork = &(m_struct->forks[index + 1]);
		index++;
	}
	return ;
}

void	finishing_threads(t_philostatus *philo, int index)
{
	int	index_x;

	index_x = 0;
	if (index == 0)
	{
		while (index < philo->mainstruct->number_of_philo)
		{
			pthread_join(philo->mainstruct->threads[index], NULL);
			index++;
		}
	}
	else
	{
		while (index_x < index)
		{
			pthread_join(philo->mainstruct->threads[index], NULL);
			index_x++;
		}
	}
	return ;
}

int	printing_action(t_philostatus *philo, int philo_id, const char *str)
{
	long	time;

	time = get_time() - philo->mainstruct->start_time;
	pthread_mutex_lock(&philo->mainstruct->mutex_lock);
	if (philo->mainstruct->someone_died == 1 \
		|| philo->mainstruct->everyone_is_full == 1)
	{
		pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
		return (-1);
	}
	pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
	pthread_mutex_lock(&philo->mainstruct->printing_lock);
	printf("%lu %i %s\n", time, philo_id, str);
	pthread_mutex_unlock(&philo->mainstruct->printing_lock);
	return (1);
}
