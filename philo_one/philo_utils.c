/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:31:20 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/06 16:19:09 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		message(char *message, int death, t_philos *philo)
{
	if (pthread_mutex_lock(philo->lock))
		return ((*philo->exit = err_message("can't lock mutex")));
	if (!(*philo->exit) || death)
		printf(message, get_time() - philo->start_time, philo->index + 1);
	if (pthread_mutex_unlock(philo->lock))
		return ((*philo->exit = err_message("can't unlock mutex")));
	return (0);
}

int		drop_forks(t_mutex *fork_1, t_mutex *fork_2)
{
	//add protect
	if (fork_1)
		pthread_mutex_unlock(fork_1);
	if (fork_2)
		pthread_mutex_unlock(fork_2);
	return (0);
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
		return (!drop_forks(first, NULL));
	message("%lu %d has taken a fork\n", 0, philo);
	if (pthread_mutex_lock(second))
	{
		pthread_mutex_unlock(first);
		return ((*philo->exit = err_message("can't lock mutex")));
	}
	if (*philo->exit)
		return (!drop_forks(first, second));
	message("%lu %d has taken a fork\n", 0, philo);
	return (0);
}

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

int		destoy_allocated(t_core *core)
{
	int		ret;

	ret = 0;
	if (pthread_mutex_destroy(&core->lock))
		ret = err_message("can't destroy mutex");
	if (destroy_mutexes(core->count_of_philos, &core->forks))
		ret = 1;
	free_memory(0, (void *)core->philos, (void *)core->forks);
	return (ret);
}
