/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_initialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:10:47 by dhussain          #+#    #+#             */
/*   Updated: 2023/08/01 18:25:06 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	*initialize_data_threads(void *data)
{
	t_philostatus	*philo;

	philo = data;
	pthread_mutex_lock(&philo->mainstruct->mutex_lock);
	if (philo->mainstruct->thread_failed == 1)
	{
		pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
		return (NULL);
	}
	fork_initialize(philo, philo->philo_id - 1);
	philo->time_must_eat = philo->mainstruct->time_to_die;
	philo->times_has_eaten = 0;
	philo->current_time = 0;
	pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
	if (philo->mainstruct->number_of_philo == 1)
		one_philo_loop(philo);
	else
		looping_operations(philo);
	return (NULL);
}

int	initialize_mutexes(t_mainstruct *m_struct)
{
	int	index;

	index = 0;
	while (index < m_struct->number_of_philo)
	{
		if (pthread_mutex_init(&(m_struct->forks[index]), NULL) == -1)
			return (-1);
		if (pthread_mutex_init(&m_struct->philo_st[index].mutex_must_eating, \
			NULL) == -1)
			return (-1);
		index++;
	}
	if (pthread_mutex_init(&m_struct->mutex_lock, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(&m_struct->printing_lock, NULL) == -1)
		return (-1);
	return (1);
}

int	initialize_variables(t_mainstruct *m_struct)
{
	m_struct->philo_st = malloc(m_struct->number_of_philo \
		* sizeof(t_philostatus));
	if (!m_struct->philo_st)
		return (-1);
	m_struct->forks = malloc(m_struct->number_of_philo \
		* sizeof(pthread_mutex_t));
	if (!m_struct->forks)
		return (-1);
	if (initialize_mutexes(m_struct) == -1)
		return (-1);
	m_struct->thread_failed = -1;
	return (1);
}

int	initialize_threads(t_mainstruct *m_struct)
{
	int		index;

	index = 0;
	if (initialize_variables(m_struct) == -1)
		return (-1);
	pthread_mutex_lock(&m_struct->mutex_lock);
	while (index < m_struct->number_of_philo)
	{
		m_struct->philo_st[index].philo_id = index + 1;
		m_struct->philo_st[index].mainstruct = m_struct;
		if (pthread_create(&m_struct->threads[index], NULL, \
			&initialize_data_threads, &(m_struct->philo_st[index])) != 0)
		{
			m_struct->thread_failed = 1;
			finishing_threads(m_struct->philo_st, index);
			return (-1);
		}
		index++;
	}
	m_struct->start_time = get_time();
	pthread_mutex_unlock(&m_struct->mutex_lock);
	usleep((m_struct->time_to_die / 3) * 1000);
	monitoring_loop(m_struct->philo_st);
	finishing_threads(m_struct->philo_st, 0);
	return (1);
}
