/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:18:16 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/10 13:39:03 by nelisabe         ###   ########.fr       */
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
