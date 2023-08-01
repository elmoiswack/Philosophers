/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:21:05 by dhussain          #+#    #+#             */
/*   Updated: 2023/08/01 17:51:08 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

struct	s_mainstruct;

typedef struct s_philo_st {
	int					philo_id;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		mutex_must_eating;
	long				current_time;
	long				time_must_eat;
	int					times_has_eaten;
	struct s_mainstruct	*mainstruct;
}	t_philostatus;

typedef struct s_mainstruct {
	int					number_of_philo;
	long				start_time;
	int					time_to_eat;
	int					time_to_die;
	int					time_to_sleep;
	int					ammount_of_eating;
	int					someone_died;
	int					everyone_is_full;
	int					philo_that_full;
	int					thread_failed;
	pthread_t			*threads;
	pthread_mutex_t		*forks;
	pthread_mutex_t		mutex_lock;
	pthread_mutex_t		printing_lock;
	pthread_mutex_t		mutex_death_lock;
	struct s_philo_st	*philo_st;
}	t_mainstruct;

//Arguments
int		arg_checker(int argc, char *argv[]);
int		filling_struct(char *argv[], t_mainstruct *m_struct);
//Arguments Utils
int		my_atoi(char *str);
int		my_strlenght(char *str);
char	*my_strcpy(char *dest, const char *src);
int		my_is_digit(int c);
void	*my_calloc(size_t count, size_t size);

//Error and Free functions
int		error_print(char *str, t_mainstruct *m_struct);
void	free_struct(t_mainstruct *m_struct);
void	delete_mutexes(t_mainstruct *m_struct);
//Thread functions
int		initialize_threads(t_mainstruct *m_struct);
int		initialize_mutexes(t_mainstruct *m_struct);
void	*initialize_data_threads(void *data);
int		monitoring_loop(t_philostatus *philo);
int		looping_operations(t_philostatus *philo);
int		one_philo_loop(t_philostatus *philo);

//Philo operations
int		philo_steal_fork(t_philostatus *philo, int philo_id);
int		philo_eating(t_philostatus *philo, int philo_id);
int		philo_thinking(t_philostatus *philo, int philo_id);
int		philo_sleeping(t_philostatus *philo, int philo_id);
int		philo_died(t_philostatus *philo, int philo_id);

//Utils
long	get_time(void);
int		sleeptight_function(long time, t_philostatus *philo);
void	finishing_threads(t_philostatus *philo, int index);
void	fork_initialize(t_philostatus *philo, int index);
int		printing_action(t_philostatus *philo, int philo_id, const char *str);

#endif