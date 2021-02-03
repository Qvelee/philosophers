/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:31:20 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/03 16:52:06 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		drop_forks(t_mutex *fork_1, t_mutex *fork_2)
{
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

	first = philo->index % 2 ? philo->left_fork : philo->rigth_fork;
	second = philo->index % 2 ? philo->rigth_fork : philo->left_fork;
	if (pthread_mutex_lock(first))
		return ((*philo->exit = err_message("can't lock mutex")));
	if (*philo->exit)
		return (!drop_forks(first, NULL));
	printf("%lu %d has taken a fork\n", \
		get_time() - philo->start_time, philo->index + 1);
	if (pthread_mutex_lock(second))
	{
		pthread_mutex_unlock(first);
		return ((*philo->exit = err_message("can't lock mutex")));
	}
	if (*philo->exit)
		return (!drop_forks(first, second));
	printf("%lu %d has taken a fork\n", \
		get_time() - philo->start_time, philo->index + 1);
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

void	destoy_allocated(t_core *core)
{
	pthread_mutex_destroy(&core->lock);
	destroy_mutexes(core->count_of_philos, &core->forks);
	free_memory(0, (void *)core->philos, (void *)core->forks);
}


