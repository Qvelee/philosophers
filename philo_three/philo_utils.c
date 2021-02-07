/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:31:20 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/07 16:18:02 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		message(char *message, int death, t_core *core)
{
	if (sem_wait(core->lock))
		return ((core->exit = err_message("can't access semaphore")));
	if (!(core->exit) || death)
		printf(message, get_time() - core->start_time, core->index + 1);
	if (sem_post(core->lock))
		return ((core->exit = err_message("can't access semaphore")));
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

int		take_forks(t_core *core)
{
	if (sem_wait(core->wait))
		return ((core->exit = err_message("can't access semaphore")));
	if (sem_wait(core->forks))
	{
		post_semaphores(core->wait, 1, NULL);
		return ((core->exit = err_message("can't access semaphore")));
	}
	if (core->exit)
		return (!post_semaphores(core->forks, 1, core->wait));
	message("%lu %d has taken a fork\n", 0, core);
	if (sem_wait(core->forks))
	{
		post_semaphores(core->forks, 1, core->wait);
		return ((core->exit = err_message("can't access semaphore")));
	}
	if (core->exit)
		return (!post_semaphores(core->forks, 2, core->wait));
	post_semaphores(core->wait, 1, NULL);
	message("%lu %d has taken a fork\n", 0, core);
	return (0);
}

int		wait_any_process(void)
{
	int		status;
	
	if ((waitpid(-1, &status, WUNTRACED) == -1))
		return (err_message("waitpid failure"));
	while (!WIFEXITED(status) && !WIFSIGNALED(status))
		if ((waitpid(-1, &status, WUNTRACED) == -1))
			return (err_message("waitpid failure"));
	return (0);
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
	return (ret);
}
