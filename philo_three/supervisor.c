/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 16:30:58 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/11 13:07:14 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*exit_wait(void *link_to_core)
{
	t_core	*core;

	core = (t_core *)link_to_core;
	if (sem_wait(core->stop))
		err_message("can't access semaphore");
	kill_processes(0, core->pids, core->count_of_philos);
	core->exit = 1;
	if (sem_post(core->meals))
		err_message("can't access semaphore");
	return (NULL);
}

void	*meals_wait(void *link_to_core)
{
	t_core	*core;
	int		index;

	core = (t_core *)link_to_core;
	index = -1;
	while (!core->exit && ++index < core->count_of_philos)
		if (sem_wait(core->meals))
		{
			err_message("can't access semaphore");
			break ;
		}
	if (sem_post(core->stop))
	{
		err_message("can't access semaphore");
		kill_processes(0, core->pids, core->count_of_philos);
	}
	return (NULL);
}

void	*supervisor(void *link_to_core)
{
	t_core	*core;

	core = (t_core *)link_to_core;
	while (!core->exit)
	{
		usleep(25);
		if (get_time() - core->last_time_eat > core->time_to_die)
		{
			core->exit = 1;
			message("%lu %d died\n", 1, core);
			if (sem_post(core->stop))
				exit(err_message("can't access semaphore"));
			break ;
		}
		if (core->count_of_meals == core->count_of_eating)
		{
			if (sem_post(core->meals))
				if (sem_post(core->stop))
					exit(err_message("can't access semaphore"));
			core->count_of_eating = -1;
		}
	}
	return (NULL);
}

int		wait_everything(t_core *core)
{
	int		status;

	core->index = -1;
	while (++core->index < core->count_of_philos)
	{
		if ((waitpid(-1, &status, WUNTRACED) == -1))
		{
			err_message("waitpid failure");
			break ;
		}
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			if ((waitpid(-1, &status, WUNTRACED) == -1))
				err_message("waitpid failure");
		if ((WIFEXITED(status) && WEXITSTATUS(status)) || \
			(WIFSIGNALED(status) && WTERMSIG(status) != 9))
			return (kill_processes(1, core->pids, core->count_of_philos));
	}
	status = 0;
	if (pthread_join(core->tstop, NULL))
		status = err_message("can't join some thread");
	if (pthread_join(core->tmeals, NULL))
		status = err_message("can't join some thread");
	return (status);
}

int		create_threads(t_core *core)
{
	if (pthread_create(&core->tstop, NULL, exit_wait, (void *)core))
		return (err_message("can't create some thread"));
	if (pthread_create(&core->tmeals, NULL, meals_wait, (void *)core))
	{
		if (sem_post(core->stop))
			err_message("can't access semaphore");
		if (pthread_join(core->tstop, NULL))
			err_message("can't join some thread");
		return (err_message("can't create some thread"));
	}
	return (0);
}
