/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:31:20 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/11 11:12:27 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		wait_threads(int stop, t_philos *philos)
{
	int		index;
	int		err;

	index = -1;
	err = 0;
	while (++index < stop)
		if (pthread_join(philos[index].thread, NULL))
			err = 1;
	return (err);
}

int		message(char *message, int death, t_philos *philo)
{
	if (pthread_mutex_lock(philo->lock))
		return (err_message("can't lock mutex"));
	if (!(*philo->exit) || death)
		printf(message, get_time() - philo->start_time, philo->index + 1);
	if (pthread_mutex_unlock(philo->lock))
		return (err_message("can't unlock mutex"));
	return (0);
}

int		drop_forks(int ret, t_mutex *fork_1, t_mutex *fork_2)
{
	int		tret;

	tret = 0;
	if (fork_1)
		if (pthread_mutex_unlock(fork_1))
			tret = err_message("can't unlock mutex");
	if (fork_2)
		if (pthread_mutex_unlock(fork_2))
			tret = err_message("can't unlock mutex");
	if (tret)
		ret = tret;
	return (ret);
}

int		take_forks(t_philos *philo)
{
	t_mutex	*first;
	t_mutex	*second;

	first = philo->left_fork;
	second = philo->rigth_fork;
	if (pthread_mutex_lock(first))
		return ((*philo->exit = err_message("can't lock mutex")));
	if (*philo->exit)
		return ((*philo->exit = drop_forks(1, first, NULL)));
	if (message("%lu %d has taken a fork\n", 0, philo))
		return ((*philo->exit = drop_forks(1, first, NULL)));
	if (pthread_mutex_lock(second))
	{
		if (pthread_mutex_unlock(first))
			err_message("can't unlock mutex");
		return ((*philo->exit = err_message("can't lock mutex")));
	}
	if (*philo->exit)
		return (drop_forks(1, first, second));
	if (message("%lu %d has taken a fork\n", 0, philo))
		return ((*philo->exit = drop_forks(1, first, second)));
	return (0);
}
