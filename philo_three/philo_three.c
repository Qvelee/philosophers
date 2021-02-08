/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:16:49 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/08 17:18:44 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

// если ошибка семофара, сразу нужно убить всех, не нужно дропать вилки.

int		take_forks(t_core *core)
{
	if (sem_wait(core->wait))
		return ((core->exit = err_message("can't access semaphore")));
	if (sem_wait(core->forks))
	{
		post_sem(0, core->wait, 1, NULL);
		return ((core->exit = err_message("can't access semaphore")));
	}
	if (core->exit)
		return (post_sem(1, core->forks, 1, core->wait));
	message("%lu %d has taken a fork\n", 0, core);
	if (sem_wait(core->forks))
	{
		post_sem(0, core->forks, 1, core->wait);
		return ((core->exit = err_message("can't access semaphore")));
	}
	if (core->exit)
		return (post_sem(1, core->forks, 2, core->wait));
	post_sem(0, core->wait, 1, NULL);
	message("%lu %d has taken a fork\n", 0, core);
	return (0);
}

int		take_fork_and_eat(t_core *core)
{
	if (core->exit)
		return (1);
	if (take_forks(core))
		return (1);
	if (!(core->exit))
	{
		core->last_time_eat = get_time();
		message("%lu %d is eating\n", 0, core);
		mssleep(core->time_to_eat);
		core->count_of_meals++;
	}
	post_sem(0, core->forks, 2, NULL);
	return (0);
}

int		goto_sleep(t_core *core)
{
	if (core->exit)
		return (1);
	message("%lu %d is sleeping\n", 0, core);
	mssleep(core->time_to_sleep);
	if (core->exit)
		return (1);
	message("%lu %d is thinking\n", 0, core);
	return (0);
}

void	*philosopher(void *link_to_core)
{
	t_core	*core;

	core = (t_core *)link_to_core;
	while (!core->exit)
	{
		if (take_fork_and_eat(core))
			break ;
		if (goto_sleep(core))
			break ;
	}
	return (NULL);
}

void	philos(t_core *core)
{
	pthread_t	stop;

	if (pthread_create(&core->thread, NULL, philosopher, (void *)core))
	{
		err_message("can't create thread");
		if (sem_post(core->stop))
			exit(err_message("can't access semaphore"));
	}
	supervisor(core);
	if (pthread_join(core->thread, NULL))
		err_message("can't join some thread");
	if (sem_post(core->stop))
		exit(err_message("can't access semaphore"));
}
