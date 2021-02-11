/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:16:49 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/11 14:08:13 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	supervisor(t_core *core)
{
	int		index;
	int		meals;

	while (!core->exit)
	{
		usleep(25);
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
		{
			return ((*philo->exit = \
				post_sem(1, philo->forks, 2, NULL)));
		}
		philo->count_of_meals++;
		mssleep(philo->time_to_eat);
	}
	if (post_sem(0, philo->forks, 2, NULL))
		return ((*philo->exit = 1));
	return (0);
}

int		goto_sleep(t_philos *philo)
{
	if (*philo->exit)
		return (1);
	if (message("%lu %d is sleeping\n", 0, philo))
		return ((*philo->exit = 1));
	mssleep(philo->time_to_sleep);
	if (*philo->exit)
		return (1);
	if (message("%lu %d is thinking\n", 0, philo))
		return ((*philo->exit = 1));
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
	return (NULL);
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
			if (wait_threads(index, core->philos))
				return (err_message("can't join some thread"));
			return (err_message("can't create thread"));
		}
	}
	supervisor(core);
	if (wait_threads(core->count_of_philos, core->philos))
		return (err_message("can't join some thread"));
	return (0);
}
