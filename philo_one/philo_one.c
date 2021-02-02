/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:16:49 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/02 19:55:34 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*philopher(void *link_to_core)
{
	t_core	*core;
	int		thread_philo;

	core = (t_core *)link_to_core;
	printf("%d\n", core->index);
	thread_philo = core->index;
	// printf("Philosopher %d is up\n", thread_philo);
	if (thread_philo == 0)
	{
		usleep(1000000);
		// printf("Philosopher %d is still up\n", thread_philo);
	}
	return NULL;
}

// add all philos parameters in philos array

int		start_philos(t_core *core)
{
	int		index;

	index = -1;
	while (++index < core->count_of_philos)
	{
		core->philos[index].index = index;
		core->index = index;
		// printf("%d\n", core->index);
		if (pthread_create(&core->philos[index].thread, NULL, \
			philopher, (void *)core))
		{
			core->exit = 1;
			wait_threads(index, core->philos);
			return (err_message("can't create thread"));
		}
		usleep(100);
	}
	if (wait_threads(core->count_of_philos, core->philos))
		return (err_message("can't join some thread"));
	return (0);
}
