/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:19:24 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/08 16:09:50 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	close_sem(int ret, sem_t *first, sem_t *second, sem_t *third)
{
	if (first)
		if (sem_close(first))
			err_message("can't close semaphore");
	if (second)
		if (sem_close(second))
			err_message("can't close semaphore");
	if (third)
		if (sem_close(third))
			err_message("can't close semaphore");
	return (ret);
}

static int	unlink_sems(t_core *core)
{
	if (sem_unlink("forks"))
		return (1);
	if (sem_unlink("lock"))
		return (1);
	if (sem_unlink("wait"))
		return (1);
	if (sem_unlink("stop"))
		return (1);
	if (sem_unlink("meals"))
		return (1);
	return (0);
}

static int	init_semaphores(t_core *core)
{
	if (unlink_sems(core))
		return (err_message("can't unlink semaphore"));
	if (!(core->forks = sem_open("forks", O_CREAT, 0644, \
		core->count_of_philos)))
		return (err_message("can't create semaphore"));
	if (!(core->lock = sem_open("lock", O_CREAT, 0644, 1)))
		return (close_sem(err_message("can't create semaphore"), \
			core->forks, NULL, NULL));
	if (!(core->wait = sem_open("wait", O_CREAT, 0644, 1)))
		return (close_sem(err_message("can't create semaphore"), \
			core->forks, core->lock, NULL));
	if (!(core->stop = sem_open("stop", O_CREAT, 0644, 0)))
		return (close_sem(err_message("can't create semaphore"), \
			core->forks, core->lock, core->stop));
	if (!(core->meals = sem_open("meals", O_CREAT, 0644, 0)))
		return (close_sem(err_message("can't create semaphore"), \
			core->forks, core->lock, core->stop) && \
			close_sem(1, core->stop, NULL, NULL));
	return (0);
}

int			init_philos(t_core *core)
{
	if (!(core->pids = (pid_t *)malloc(sizeof(core->count_of_philos))))
		return (1);
	memset((void *)core->pids, 0, core->count_of_philos);
	if (init_semaphores(core))
		return (free_memory(1, core->pids, NULL));
	core->start_time = get_time();
	core->last_time_eat = get_time();
	core->count_of_meals = 0;
	core->exit = 0;
	return (0);
}
