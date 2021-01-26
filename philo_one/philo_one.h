/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:38:57 by nelisabe          #+#    #+#             */
/*   Updated: 2021/01/26 18:38:09 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#include <stdio.h>

#define	ERR_ARGS "error: wrong number of arguments"
#define	ERR_INV_ARGS "error: invalid argument"
#define ERR_MALLOC "error: can't allocate memory with malloc"
#define ERR_SMTNWR "error: something went wrong"

typedef	pthread_mutex_t	t_mutex;

typedef	struct	s_philos
{
	int			status;
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
	t_mutex		lock;
	t_mutex		*forks;
	int			exit;
	t_philos	*philos;
}				t_core;

int		parse(int argc, char **argv, t_core *core);
int		init_philosophers(t_core *core);
long	ft_atol(const char *str);
int		ft_isdigit(int c);
int		free_memory(int ret, void *mem_1, void *mem_2, void *mem_3);
int		err_arguments(void);
int		err_invalid_argument(char *argument);
int		err_malloc(void);
int		err_message(char *message);

#endif
