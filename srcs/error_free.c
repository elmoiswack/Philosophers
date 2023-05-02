/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:43:33 by dhussain          #+#    #+#             */
/*   Updated: 2023/05/02 18:17:24 by dhussain         ###   ########.fr       */
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

void	free_struct(t_mainstruct *m_struct)
{
	free(m_struct->philo_st);
	free(m_struct);
}