/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:31:20 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/08 17:18:17 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		message(char *message, int death, t_core *core)
{
	if (sem_wait(core->lock))
		return ((core->exit = err_message("can't access semaphore")));
	if (!(core->exit) || death)
		printf(message, get_time() - core->start_time, core->index + 1);
	if (!death && sem_post(core->lock))
		return ((core->exit = err_message("can't access semaphore")));
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
