/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:16:49 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/10 18:21:56 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		take_forks(t_core *core)
{
	if (sem_wait(core->wait))
		return (sem_failure(core->stop, &core->exit));
	if (sem_wait(core->forks))
		return (sem_failure(core->stop, &core->exit));
	if (core->exit)
		return (1);
	if (message("%lu %d has taken a fork\n", 0, core))
		return (1);
	if (sem_wait(core->forks))
		return (sem_failure(core->stop, &core->exit));
	if (core->exit)
		return (1);
	if (post_sem(0, core->wait, 1, NULL))
		return (sem_failure(core->stop, &core->exit));
	if (message("%lu %d has taken a fork\n", 0, core))
		return (1);
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
		if (message("%lu %d is eating\n", 0, core))
			return (sem_failure(core->stop, &core->exit));
		mssleep(core->time_to_eat);
		core->count_of_meals++;
	}
	if (post_sem(0, core->forks, 2, NULL))
		return (sem_failure(core->stop, &core->exit));
	return (0);
}

int		goto_sleep(t_core *core)
{
	if (core->exit)
		return (1);
	if (message("%lu %d is sleeping\n", 0, core))
		return (sem_failure(core->stop, &core->exit));
	mssleep(core->time_to_sleep);
	if (core->exit)
		return (1);
	if (message("%lu %d is thinking\n", 0, core))
		return (sem_failure(core->stop, &core->exit));
	return (0);
}

void	philosopher(t_core *core)
{
	while (!core->exit)
	{
		if (take_fork_and_eat(core))
			break ;
		if (goto_sleep(core))
			break ;
	}
}

void	philos(t_core *core)
{
	pthread_t	stop;

	if (pthread_create(&core->thread, NULL, supervisor, (void *)core))
	{
		err_message("can't create thread");
		if (sem_post(core->stop))
			exit(err_message("can't access semaphore"));
	}
	philosopher(core);
	if (pthread_join(core->thread, NULL))
		err_message("can't join some thread");
	if (sem_post(core->stop))
		exit(err_message("can't access semaphore"));
}
