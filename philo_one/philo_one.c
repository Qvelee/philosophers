/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:16:49 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/03 16:54:34 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	supervisor(t_core *core)
{
	int		index;
	
	while (!core->exit)
	{
		index = -1;
		while (++index < core->count_of_philos)
			if (get_time() - core->philos[index].last_time_eat > \
				core->time_to_die)
			{
				core->exit = 1;
				printf("%lu %d died\n", \
					get_time() - core->start_time, index + 1);
				break ;
			}
	}
}

int		take_fork_and_eat(t_philos *philo)
{
	if (*philo->exit)
		return (1);
	if (take_forks(philo))
		return (1);
	if (!(*philo->exit))
	{
		philo->last_time_eat = get_time();
		printf("%lu %d is eating\n", \
			get_time() - philo->start_time, philo->index + 1);
		mssleep(philo->time_to_eat);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->rigth_fork);
	return (0);
}

int		goto_sleep(t_philos *philo)
{
	if (*philo->exit)
		return (1);
	printf("%lu %d is sleeping\n", \
		get_time() - philo->start_time, philo->index + 1);
	mssleep(philo->time_to_sleep);
	if (*philo->exit)
		return (1);
	printf("%lu %d is thinking\n", \
		get_time() - philo->start_time, philo->index + 1);
	return (0);
}

void	*philosopher(void *link_to_philo)
{
	t_philos	*philo;

	philo = (t_philos *)link_to_philo;
	while (!(*philo->exit))
	{
		if (take_fork_and_eat(philo))
			break ;
		if (goto_sleep(philo))
			break ;
	}
	return NULL;
}

int		start_philos(t_core *core)
{
	int		index;

	index = -1;
	while (++index < core->count_of_philos)
	{
		if (pthread_create(&core->philos[index].thread, NULL, \
			philosopher, (void *)&core->philos[index]))
		{
			core->exit = 1;
			wait_threads(index, core->philos);
			return (err_message("can't create thread"));
		}
	}
	supervisor(core);
	if (wait_threads(core->count_of_philos, core->philos))
		return (err_message("can't join some thread"));
	return (0);
}
