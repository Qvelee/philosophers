/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:31:20 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/06 17:32:54 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		message(char *message, int death, t_philos *philo)
{
	if (sem_wait(philo->lock))
		return ((*philo->exit = err_message("can't access semaphore")));
	if (!(*philo->exit) || death)
		printf(message, get_time() - philo->start_time, philo->index + 1);
	if (sem_post(philo->lock))
		return ((*philo->exit = err_message("can't access semaphore")));
	return (0);
}

int		post_semaphores(sem_t *sem_1, int count, sem_t *sem_2)
{
	if (sem_post(sem_1))
		return (err_message("can't access semaphore"));
	if (count > 1 && sem_post(sem_1))
		return (err_message("can't access semaphore"));
	if (sem_2 && sem_post(sem_2))
		return (err_message("can't access semaphore"));
	return (0);
}

int		take_forks(t_philos *philo)
{
	if (sem_wait(philo->wait))
		return ((*philo->exit = err_message("can't access semaphore")));
	if (sem_wait(philo->forks))
	{
		post_semaphores(philo->wait, 1, NULL);
		return ((*philo->exit = err_message("can't access semaphore")));
	}
	if (*philo->exit)
		return (!post_semaphores(philo->forks, 1, philo->wait));
	message("%lu %d has taken a fork\n", 0, philo);
	if (sem_wait(philo->forks))
	{
		post_semaphores(philo->forks, 1, philo->wait);
		return ((*philo->exit = err_message("can't access semaphore")));
	}
	if (*philo->exit)
		return (!post_semaphores(philo->forks, 2, philo->wait));
	post_semaphores(philo->wait, 1, NULL);
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
	if (sem_close(core->forks))
		ret = err_message("can't close semaphore");
	if (sem_close(core->lock))
		ret = err_message("can't close semaphore");
	free_memory(0, (void *)core->philos, NULL);
	return (ret);
}
