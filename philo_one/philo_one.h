/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:38:57 by nelisabe          #+#    #+#             */
/*   Updated: 2021/01/14 17:34:13 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#include <stdio.h>

#define	ERR_ARGS "Error: wrong number of arguments"
#define	ERR_INV_ARGS "Error: invalid argument"
#define ERR_MALLOC "Error: can't allocate memory with malloc"

typedef	struct	s_params
{
	int		number;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int		count_of_eating;
	int		*status;
}				t_params;

int		ft_atoi(const char *str);
char	*ft_itoa(int number);
int		err_arguments(void);
int		err_invalid_argument(char *argument);
int		err_malloc(void);

#endif
