/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:16:49 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/07 19:15:12 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
		core->count_of_meals++;
		mssleep(core->time_to_eat);
	}
	post_semaphores(core->forks, 2, NULL);
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

int		philos(t_core *core)
{
	pthread_t	stop;

	if (pthread_create(&core->thread, NULL, philosopher, (void *)core))
	{
		sem_post(core->stop);
		exit(err_message("can't create thread"));
	}
	if (pthread_create(&stop, NULL, exit_wait, (void *)core))
	{
		core->exit = 1;
		sem_post(core->stop);
		pthread_join(core->thread, NULL);
		exit(err_message("can't create thread"));
	}
	supervisor(core);
	pthread_join(core->thread, NULL);
	pthread_join(stop, NULL);
	exit(0);
}

int		start_philos(t_core *core)
{
	pid_t	pid;

	core->index = -1;
	while (++core->index < core->count_of_philos)
	{
		pid = fork();
		if (pid == 0)
			philos(core);
		else if (pid < 0)
		{
			sem_post(core->stop);
			return (err_message("can't create new process"));
		}
	}
	core->index = -1;
	while (++core->index < core->count_of_philos)
		wait_any_process();
	return (0);
}
