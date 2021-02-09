/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:31:20 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/09 16:48:19 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		message(char *message, int death, t_philos *philo)
{
	if (pthread_mutex_lock(philo->lock))
		return (err_message("can't lock mutex"));
	if (!(*philo->exit) || death)
		printf(message, get_time() - philo->start_time, philo->index + 1);
	if (pthread_mutex_unlock(philo->lock))
		return (err_message("can't unlock mutex"));
	return (0);
}

int		drop_forks(t_mutex *fork_1, t_mutex *fork_2)
{
	if (fork_1)
		if (pthread_mutex_unlock(fork_1))
			err_message("can't unlock mutex");
	if (fork_2)
		if (pthread_mutex_unlock(fork_2))
			err_message("can't unlock mutex");
	return (0);
}

int		take_forks(t_philos *philo)
{
	t_mutex	*first;
	t_mutex	*second;

	first = philo->left_fork;
	second = philo->rigth_fork;
	if (pthread_mutex_lock(first))
		return ((*philo->exit = err_message("can't lock mutex")));
	if (*philo->exit)
		return ((*philo->exit = !drop_forks(first, NULL)));
	if (message("%lu %d has taken a fork\n", 0, philo))
		return ((*philo->exit = !drop_forks(first, NULL)));
	if (pthread_mutex_lock(second))
	{
		if (pthread_mutex_unlock(first))
			err_message("can't unlock mutex");
		return ((*philo->exit = err_message("can't lock mutex")));
	}
	if (*philo->exit)
		return (!drop_forks(first, second));
	if (message("%lu %d has taken a fork\n", 0, philo))
		return ((*philo->exit = !drop_forks(first, second)));
	return (0);
}
