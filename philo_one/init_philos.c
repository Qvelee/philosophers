/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:19:24 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/02 19:29:39 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	destroy_mutexes(int stop, t_mutex **mutexes)
{
	int		index;

	index = -1;
	while (++index < stop)
		pthread_mutex_destroy(&(*mutexes)[index]);
}

int		init_mutexes(t_core *core)
{
	int 	index;

	index = -1;
	if (pthread_mutex_init(&core->lock, NULL))
		return (1);
	while (++index < core->count_of_philos)
		if (pthread_mutex_init(&core->forks[index], NULL))
		{
			destroy_mutexes(index, &core->forks);
			pthread_mutex_destroy(&core->lock);
			return (1);
		}
	return (0);
}

void	set_philos_values(t_core *core)
{
	int		index;
	int		left_fork;
	int		right_fork;

	index = -1;
	while (++index < core->count_of_philos)
	{
		core->philos[index].status = 1;
		core->philos[index].last_time_eat = 0;
		core->philos[index].index = index;
		left_fork = !index ? core->count_of_philos - 1 : index - 1;
		right_fork = index == core->count_of_philos	- 1 ? 0 : index;
		core->philos[index].left_fork = &core->forks[left_fork];
		core->philos[index].rigth_fork = &core->forks[right_fork];
	}
}

int		init_philos(t_core *core)
{
	if (!(core->philos = \
		(t_philos *)malloc(sizeof(t_philos) * core->count_of_philos)))
		return (err_malloc());
	if (!(core->forks = \
		(t_mutex *)malloc(sizeof(t_mutex) * core->count_of_philos)))
		return (free_memory(err_malloc(), (void *)core->philos, NULL));
	if (init_mutexes(core))
		return (free_memory(err_message("can't init mutex"), \
			(void *)core->philos, (void *)core->forks));
	set_philos_values(core);
	core->start_time = get_time();
	core->index = 0;
	core->exit = 0;
	return (0);
}
