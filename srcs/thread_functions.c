/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 23:16:41 by dhussain          #+#    #+#             */
/*   Updated: 2023/04/14 15:48:19 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include "pthread.h"
#include <unistd.h>
#include "stdio.h"

void	lmao_xd(void *data)
{
	char *str;

	str = (char *) data;
	for (int i = 0; i < 120; i++)
	{
		usleep(50);
		printf("%s\n\n", str);
	}
	printf("finished!!!\n");
}

int	initializing_threads(t_mainstruct *m_struct, char *argv[])
{
	pthread_t	thread1;
	pthread_t	thread2;

	m_struct->number_philo = my_atoi(argv[1]);
	pthread_create(&thread2, NULL, (void *)lmao_xd, "wow");
	pthread_create(&thread1, NULL, (void *)lmao_xd, "lmao xd");
	usleep(500);
	printf("finished yes xd!\n");
	// pthread_join(thread1, NULL);
	// pthread_join(thread2, NULL);
	return (1);
}
