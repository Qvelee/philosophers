/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:19:24 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/06 17:09:42 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		init_semaphores(t_core *core)
{
	//fix
	sem_unlink("forks");
	sem_unlink("lock");
	sem_unlink("wait");
	if (!(core->forks = sem_open("forks", O_CREAT, 0644, core->count_of_philos)))
		return (err_message("can't create semaphore"));
	if (!(core->lock = sem_open("lock", O_CREAT, 0644, 1)))
	{
		if (sem_close(core->forks))
			err_message("can't close semaphore");
		return (err_message("can't create semaphore"));
	}
	if (!(core->wait = sem_open("wait", O_CREAT, 0644, 1)))
	{
		if (sem_close(core->forks))
			err_message("can't close semaphore");
		if (sem_close(core->lock))
			err_message("can't close semaphore");
		return (err_message("can't create semaphore"));
	}
	return (0);
}

void	set_philos_values(t_core *core)
{
	int		index;

	index = -1;
	while (++index < core->count_of_philos)
	{
		core->philos[index].status = 1;
		core->philos[index].last_time_eat = get_time();
		core->philos[index].index = index;
		core->philos[index].time_to_die = core->time_to_die;
		core->philos[index].time_to_eat = core->time_to_eat;
		core->philos[index].time_to_sleep = core->time_to_sleep;
		core->philos[index].count_of_meals = 0;
		core->philos[index].start_time = core->start_time;
		core->philos[index].forks = core->forks;
		core->philos[index].lock = core->lock;
		core->philos[index].wait = core->wait;
		core->philos[index].exit = &core->exit;
	}
}

int		init_philos(t_core *core)
{
	if (!(core->philos = \
		(t_philos *)malloc(sizeof(t_philos) * core->count_of_philos)))
		return (err_malloc());
	if (init_semaphores(core))
		return (free_memory(1, (void *)core->philos, NULL));
	core->start_time = get_time();
	core->exit = 0;
	set_philos_values(core);
	return (0);
}
