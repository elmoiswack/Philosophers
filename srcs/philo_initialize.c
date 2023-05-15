/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_initialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:10:47 by dhussain          #+#    #+#             */
/*   Updated: 2023/05/15 15:58:23 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	looping_operations(t_philostatus *philo)
{
	while (1)
	{
		if (philo->dead_status == 1)
			break ;
		pthread_mutex_lock(&philo->mainstruct->mutex_lock);
		philo->time_last_eat += get_time();
		pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
		philo_thinking(philo, philo->philo_id);
		if (philo->dead_status == 1)
			break ;
		philo_steal_fork(philo, philo->philo_id);
		if (philo->dead_status == 1)
			break ;
		philo_sleeping(philo, philo->philo_id);
	}
	return (0);
}

int	monitoring_loop(t_philostatus *philo)
{
	int	index;

	index = 0;
	while (1)
	{
		if ((philo[index].time_last_eat - philo[index].start_time) >= philo[index].time_must_eat)
		{
			pthread_mutex_lock(&philo->mainstruct->mutex_death_lock);
			philo_died(philo, index);
			everyone_is_dead(philo);
			pthread_mutex_unlock(&philo->mainstruct->mutex_death_lock);
			break ;
		}
		index++;
		if (index == philo->mainstruct->number_of_philo)
			index = 0;
	}
	everyone_is_dead(philo);
	return (1);
}

void	*initialize_data_threads(void *data)
{
	t_philostatus	*philo;

	philo = data;
	pthread_mutex_lock(&philo->mainstruct->mutex_lock);
	pthread_mutex_init(&philo->left_fork, NULL);
	pthread_mutex_init(&philo->right_fork, NULL);
	philo->start_time = get_time();
	philo->time_must_eat = philo->mainstruct->time_to_die;
	philo->times_has_eaten = 0;
	philo->time_last_eat = 0;
	philo->dead_status = -1;
	philo->has_eaten_status = -1;
	pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
	looping_operations(philo);
	finishing_threads(philo);
	return (NULL);
}

int	initialize_threads(t_mainstruct *m_struct)
{
	int		index;

	index = 1;
	m_struct->philo_st = my_calloc(m_struct->number_of_philo, sizeof(t_philostatus));
	if (!m_struct->philo_st)
		return (-1);
	pthread_mutex_init(&m_struct->mutex_lock, NULL);
	pthread_mutex_init(&m_struct->mutex_eating_lock, NULL);
	pthread_mutex_init(&m_struct->mutex_sleeping_lock, NULL);
	pthread_mutex_init(&m_struct->mutex_thinking_lock, NULL);
	pthread_mutex_init(&m_struct->mutex_death_lock, NULL);
	while (index <= m_struct->number_of_philo)
	{
		m_struct->philo_st[index].philo_id = index;
		m_struct->philo_st[index].mainstruct = m_struct;
		pthread_create(&m_struct->threads[index], NULL, &initialize_data_threads, &(m_struct->philo_st[index]));
		index++;
		usleep(250);
	}
	monitoring_loop(m_struct->philo_st);
	return (1);
}
