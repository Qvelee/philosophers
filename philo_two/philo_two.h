/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:38:57 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/09 16:54:35 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>

#define	ERR_ARGS "error: wrong number of arguments"
#define	ERR_INV_ARGS "error: invalid argument"
#define ERR_MALLOC "error: can't allocate memory with malloc"
#define ERR_SMTNWR "error: something went wrong"

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
	int			*exit;
	sem_t		*forks;
	sem_t		*lock;
	sem_t		*wait;
	pthread_t	thread;
}				t_philos;

typedef	struct	s_core
{
	int			count_of_philos;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			count_of_eating;
	size_t		start_time;
	int			exit;
	sem_t		*forks;
	sem_t		*lock;
	sem_t		*wait;
	t_philos	*philos;
}				t_core;

int		parse(int argc, char **argv, t_core *core);
int		init_philos(t_core *core);
int		take_forks(t_philos *philo);
int		message(char *message, int death, t_philos *philo);
int		post_sem(int ret, sem_t *sem_1, int count, sem_t *sem_2);
int		destoy_allocated(t_core *core);
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
