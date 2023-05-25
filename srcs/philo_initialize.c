/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_initialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantehussain <dantehussain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:10:47 by dhussain          #+#    #+#             */
/*   Updated: 2023/05/25 23:45:30 by dantehussai      ###   ########.fr       */
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
	fork_initialize(philo, philo->philo_id - 1);
	philo->time_must_eat = philo->mainstruct->time_to_die;
	philo->times_has_eaten = 0;
	philo->current_time = 0;
	pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
	if (philo->philo_id % 2 == 0)
		usleep(250);
	looping_operations(philo);
	finishing_threads(philo);
	return (NULL);
}

int	initialize_mutexes(t_mainstruct *m_struct)
{
	int	index;

	index = 0;
	while (index < m_struct->number_of_philo)
	{
		pthread_mutex_init(&(m_struct->forks[index]), NULL);
		index++;
	}
	if (pthread_mutex_init(&m_struct->mutex_lock, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(&m_struct->mutex_eating_lock, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(&m_struct->mutex_sleeping_lock, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(&m_struct->mutex_thinking_lock, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(&m_struct->mutex_death_lock, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(&m_struct->printing_lock, NULL) == -1)
		return (-1);
	return (1);
}

int	initialize_threads(t_mainstruct *m_struct)
{
	int		index;

	index = 0;
	m_struct->philo_st = malloc(m_struct->number_of_philo * sizeof(t_philostatus));
	if (!m_struct->philo_st)
		return (-1);
	m_struct->forks = malloc(m_struct->number_of_philo * sizeof(pthread_mutex_t));
	if (!m_struct->forks)
		return (-1);
	if (initialize_mutexes(m_struct) == -1)
		return (-1);
	m_struct->someone_died = -1;
	m_struct->everyone_is_full = -1;
	m_struct->philo_that_full = 0;
	m_struct->start_time = get_time();
	while (index < m_struct->number_of_philo)
	{
		m_struct->philo_st[index].philo_id = index + 1;
		m_struct->philo_st[index].mainstruct = m_struct;
		if (pthread_create(&m_struct->threads[index], NULL, &initialize_data_threads, &(m_struct->philo_st[index])) == -1)
			return (-1);
		index++;
		usleep(250);
	}
	monitoring_loop(m_struct->philo_st);
	return (1);
}
