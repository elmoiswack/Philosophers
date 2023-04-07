/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:21:38 by dhussain          #+#    #+#             */
/*   Updated: 2023/04/06 12:12:59 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>
#include <unistd.h>
 #include <stdlib.h>

int	main(int argc, char *argv[])
{
	t_mainstruct *m_struct;

	if (arg_checker(argc, argv) == -1)
		return (error_print("Error\nWrong arguments"));
	m_struct = (t_mainstruct *) malloc(1 * sizeof(t_mainstruct));
	if (!m_struct)
		return (-1);
	m_struct->number_philo = my_atoi(argv[1]);
	if (m_struct->number_philo == -1)
	{
		free_struct(m_struct);
		return (-1);
	}
	printf("woooooow\n\n");
	return (0);
}