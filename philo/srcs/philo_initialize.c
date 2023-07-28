/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_initialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantehussain <dantehussain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:10:47 by dhussain          #+#    #+#             */
/*   Updated: 2023/07/28 06:41:27 by dantehussai      ###   ########.fr       */
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
	philo->start_time = get_time();
	pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
	if (philo->mainstruct->number_of_philo == 1)
		one_philo_loop(philo);
	else
		looping_operations(philo);
	finishing_threads(philo, 0);
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
	return (1);
}

int	initialize_threads(t_mainstruct *m_struct)
{
	int		index;

	index = 0;
	if (initialize_variables(m_struct) == -1)
		return (-1);
	while (index < m_struct->number_of_philo)
	{
		m_struct->philo_st[index].philo_id = index + 1;
		m_struct->philo_st[index].mainstruct = m_struct;
		if (pthread_create(&m_struct->threads[index], NULL, \
			&initialize_data_threads, &(m_struct->philo_st[index])) != 0)
		{
			finishing_threads(m_struct->philo_st, index);
			return (-1);
		}
		index++;
		usleep(250);
	}
	monitoring_loop(m_struct->philo_st);
	return (1);
}
