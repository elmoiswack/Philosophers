/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:43:33 by dhussain          #+#    #+#             */
/*   Updated: 2023/06/01 11:04:24 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>
#include <stdlib.h>

int	error_print(char *str, t_mainstruct *m_struct)
{
	if (m_struct)
		free_struct(m_struct);
	printf("%s\n", str);
	return (-1);
}

void	delete_mutexes(t_mainstruct *m_struct)
{
	int	index;

	index = 0;
	while (index < m_struct->number_of_threads)
	{
		pthread_mutex_destroy(m_struct->philo_st[index].left_fork);
		pthread_mutex_destroy(m_struct->philo_st[index].right_fork);
		index++;
	}
	pthread_mutex_destroy(&m_struct->mutex_lock);
	pthread_mutex_destroy(&m_struct->mutex_eating_lock);
	pthread_mutex_destroy(&m_struct->mutex_sleeping_lock);
	pthread_mutex_destroy(&m_struct->mutex_thinking_lock);
	pthread_mutex_destroy(&m_struct->mutex_death_lock);
}

void	free_struct(t_mainstruct *m_struct)
{
	delete_mutexes(m_struct);
	free(m_struct->threads);
	free(m_struct->forks);
	free(m_struct->philo_st);
	free(m_struct);
}
