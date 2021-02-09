/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:16:49 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/09 16:34:02 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		wait_threads(int stop, t_philos *philos)
{
	int		index;
	int		err;

	index = -1;
	err = 0;
	while (++index < stop)
		if (pthread_join(philos[index].thread, NULL))
			err = 1;
	return (err);
}

void	supervisor(t_core *core)
{
	int		index;
	int		meals;
	
	while (!core->exit)
	{
		index = -1;
		meals = 0;
		while (++index < core->count_of_philos)
		{
			if (get_time() - core->philos[index].last_time_eat > \
				core->time_to_die)
			{
				core->exit = 1;
				message("%lu %d died\n", 1, &core->philos[index]);
				break ;
			}
			if (core->count_of_eating == -1 || \
				core->philos[index].count_of_meals < core->count_of_eating)
				meals = 1;
		}
		if (!meals)
			core->exit = 1;
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
		if (message("%lu %d is eating\n", 0, philo))
			return ((*philo->exit = \
				!drop_forks(philo->left_fork, philo->rigth_fork)));
		philo->count_of_meals++;
		mssleep(philo->time_to_eat);
	}
	drop_forks(philo->left_fork, philo->rigth_fork);
	return (0);
}

int		goto_sleep(t_philos *philo)
{
	if (*philo->exit)
		return (1);
	if (message("%lu %d is sleeping\n", 0, philo))
		return (*philo->exit = 1);
	mssleep(philo->time_to_sleep);
	if (*philo->exit)
		return (1);
	if (message("%lu %d is thinking\n", 0, philo))
		return (*philo->exit = 1);
	return (0);
}

void	*philosopher(void *link_to_philo)
{
	t_philos	*philo;

	philo = (t_philos *)link_to_philo;
	if (philo->index % 2)
		usleep(100);
	while (!(*philo->exit))
	{
		if (take_fork_and_eat(philo))
			break ;
		if (goto_sleep(philo))
			break ;
	}
	return (NULL);
}
