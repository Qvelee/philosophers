/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:31:20 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/09 17:14:44 by nelisabe         ###   ########.fr       */
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

int		post_sem(int ret, sem_t *sem_1, int count, sem_t *sem_2)
{
	int		tret;

	tret = 0;
	if (sem_post(sem_1))
		tret = err_message("can't access semaphore");
	else if (count > 1 && sem_post(sem_1))
		tret = err_message("can't access semaphore");
	else if (sem_2 && sem_post(sem_2))
		tret = err_message("can't access semaphore");
	if (tret)
		ret = tret;
	return (ret);
}

int		take_forks(t_philos *philo)
{
	if (sem_wait(philo->wait))
		return ((*philo->exit = err_message("can't access semaphore")));
	if (sem_wait(philo->forks))
	{
		post_sem(0, philo->wait, 1, NULL);
		return ((*philo->exit = err_message("can't access semaphore")));
	}
	if (*philo->exit)
		return (post_sem(1, philo->forks, 1, philo->wait));
	if (message("%lu %d has taken a fork\n", 0, philo))
		return ((*philo->exit = post_sem(1, philo->forks, 1, philo->wait)));
	if (sem_wait(philo->forks))
	{
		post_sem(1, philo->forks, 1, philo->wait);
		return ((*philo->exit = err_message("can't access semaphore")));
	}
	if (*philo->exit)
		return (post_sem(1, philo->forks, 2, philo->wait));
	if (post_sem(0, philo->wait, 1, NULL))
		return ((*philo->exit = post_sem(1, philo->forks, 1, philo->wait)));
	if (message("%lu %d has taken a fork\n", 0, philo))
		return ((*philo->exit = post_sem(1, philo->forks, 1, philo->wait)));
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
