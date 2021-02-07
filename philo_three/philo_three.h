/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:38:57 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/07 17:07:42 by nelisabe         ###   ########.fr       */
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
#include <sys/types.h>
#include <sys/wait.h>

#define	ERR_ARGS "error: wrong number of arguments"
#define	ERR_INV_ARGS "error: invalid argument"
#define ERR_MALLOC "error: can't allocate memory with malloc"
#define ERR_SMTNWR "error: something went wrong"

typedef	struct	s_core
{
	int			index;
	int			count_of_philos;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			count_of_eating;
	int			count_of_meals;
	size_t		start_time;
	size_t		last_time_eat;
	int			exit;
	sem_t		*forks;
	sem_t		*lock;
	sem_t		*wait;
	sem_t		*stop;
	pthread_t	thread;
}				t_core;

int		parse(int argc, char **argv, t_core *core);
int		init_philos(t_core *core);
int		take_forks(t_core *core);
int		message(char *message, int death, t_core *core);
int		post_semaphores(sem_t *sem_1, int count_1, sem_t *sem_2);
int		destoy_allocated(t_core *core);
int		wait_any_process(void);
int		get_time(void);
int		start_philos(t_core *core);
void	supervisor(t_core *core);
void	*exit_wait(void *link_to_core);
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
