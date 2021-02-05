/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:38:57 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/05 14:51:38 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>

#define	ERR_ARGS "error: wrong number of arguments"
#define	ERR_INV_ARGS "error: invalid argument"
#define ERR_MALLOC "error: can't allocate memory with malloc"
#define ERR_SMTNWR "error: something went wrong"

typedef	pthread_mutex_t	t_mutex;

typedef	struct	s_philos
{
	int			status;
	int			index;
	size_t		last_time_eat;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			count_of_meals;
	size_t		start_time;
	t_mutex		*lock;
	int			*exit;
	pthread_t	thread;
	t_mutex		*left_fork;
	t_mutex		*rigth_fork;
}				t_philos;

typedef	struct	s_core
{
	int			count_of_philos;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			count_of_eating;
	size_t		start_time;
	t_mutex		lock;
	t_mutex		*forks;
	int			exit;
	t_philos	*philos;
}				t_core;

int		parse(int argc, char **argv, t_core *core);
int		init_philos(t_core *core);
int		take_forks(t_philos *philo);
int		message(char *message, int death, t_philos *philo);
int		drop_forks(t_mutex *fork_1, t_mutex *fork_2);
void	destroy_mutexes(int stop, t_mutex **mutexes);
void	destoy_allocated(t_core *core);
int		wait_threads(int stop, t_philos *philos);
int		get_time(void);
int		start_philos(t_core *core);
int		mssleep(size_t msseconds);
long	ft_atol(const char *str);
int		ft_isdigit(int c);
int		free_memory(int ret, void *mem_1, void *mem_2);
int		err_arguments(void);
int		err_invalid_argument(char *argument);
int		err_malloc(void);
int		err_message(char *message);
int		err_philos(t_core *core);

#endif
