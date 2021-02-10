/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:38:57 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/10 16:34:29 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>
# define ERR_ARGS "error: wrong number of arguments"
# define ERR_INV_ARGS "error: invalid argument"
# define ERR_MALLOC "error: can't allocate memory with malloc"
# define ERR_SMTNWR "error: something went wrong"

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
	pid_t		*pids;
	sem_t		*forks;
	sem_t		*lock;
	sem_t		*wait;
	sem_t		*stop;
	sem_t		*meals;
	pthread_t	thread;
	pthread_t	tstop;
	pthread_t	tmeals;
}				t_core;

int				destoy_allocated(t_core *core);
int				parse(int argc, char **argv, t_core *core);
int				init_philos(t_core *core);
int				start_philos(t_core *core);
int				create_threads(t_core *core);
int				fork_failure(t_core *core);
void			*supervisor(void *link_to_core);
void			philos(t_core *core);
int				wait_everything(t_core *core);
int				kill_processes(int ret, pid_t *pids, int count);
int				take_forks(t_core *core);
int				post_sem(int ret, sem_t *sem_1, int count_1, sem_t *sem_2);
int				sem_failure(sem_t *sem, int *exit);
int				message(char *message, int death, t_core *core);
int				get_time(void);
void			*exit_wait(void *link_to_core);
void			*meals_wait(void *link_to_core);
int				mssleep(size_t msseconds);
long			ft_atol(const char *str);
int				ft_isdigit(int c);
int				free_memory(int ret, void *mem_1, void *mem_2);
int				err_arguments(void);
int				err_invalid_argument(char *argument);
int				err_malloc(void);
int				err_message(char *message);
int				err_philos(t_core *core);

#endif
