/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:18:16 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/09 16:43:31 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
	free_memory(0, (void *)core->philos, NULL);
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
