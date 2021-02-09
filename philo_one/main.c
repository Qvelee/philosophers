/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:18:16 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/09 12:25:54 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		destoy_allocated(t_core *core)
{
	int		ret;

	ret = 0;
	if (pthread_mutex_destroy(&core->lock))
		ret = err_message("can't destroy mutex");
	if (destroy_mutexes(core->count_of_philos, &core->forks))
		ret = 1;
	free_memory(0, (void *)core->philos, (void *)core->forks);
	return (ret);
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
