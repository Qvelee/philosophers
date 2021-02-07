/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:19:24 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/07 16:18:48 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		close_sem(int ret, sem_t *first, sem_t *second, sem_t *third)
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

int		init_semaphores(t_core *core)
{
	//fix
	sem_unlink("forks");
	sem_unlink("lock");
	sem_unlink("wait");
	sem_unlink("stop");
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
	return (0);
}

int		init_philos(t_core *core)
{
	if (init_semaphores(core))
		return (1);
	core->start_time = get_time();
	core->last_time_eat = get_time();
	core->count_of_meals = 0;
	core->exit = 0;
	return (0);
}
