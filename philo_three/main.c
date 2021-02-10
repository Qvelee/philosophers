/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:18:16 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/10 15:18:45 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		fork_failure(t_core *core)
{
	if (sem_post(core->stop))
	{
		kill_processes(0, core->pids, core->index);
		err_message("can't access semaphore");
	}
	return (err_message("can't create new process"));
}

int		kill_processes(int ret, pid_t *pids, int count)
{
	int		index;

	index = -1;
	while (++index < count && pids[index])
		kill(pids[index], SIGKILL);
	return (1);
}

int		destoy_allocated(t_core *core)
{
	int		ret;

	ret = 0;
	if (sem_close(core->forks))
		ret = err_message("can't close semaphore");
	if (sem_close(core->lock))
		ret = err_message("can't close semaphore");
	if (sem_close(core->wait))
		ret = err_message("can't close semaphore");
	if (sem_close(core->stop))
		ret = err_message("can't close semaphore");
	if (sem_close(core->meals))
		ret = err_message("can't close semaphore");
	free_memory(0, core->pids, NULL);
	return (ret);
}

int		start_philos(t_core *core)
{
	pid_t		pid;

	if (create_threads(core))
		return (1);
	core->index = -1;
	while (++core->index < core->count_of_philos)
	{
		pid = fork();
		if (pid == 0)
			philos(core);
		else if (pid < 0)
		{
			fork_failure(core);
			break ;
		}
		core->pids[core->index] = pid;
	}
	if (wait_everything(core))
		return (1);
	return (0);
}

int		main(int argc, char **argv)
{
	t_core	core;

	if (parse(argc, argv, &core))
		return (1);
	if (init_philos(&core))
		return (1);
	if (start_philos(&core))
		return (err_philos(&core));
	if (destoy_allocated(&core))
		return (1);
	return (0);
}
