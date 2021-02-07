/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 16:30:58 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/07 17:15:35 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*exit_wait(void *link_to_core)
{
	t_core	*core;

	core = (t_core *)link_to_core;
	sem_wait(core->stop);
	sem_post(core->stop);
	core->exit = 1;
	return (NULL);
}

void	supervisor(t_core *core)
{
	int			meals;
	
	while (!core->exit)
	{
		meals = 0;
		if (get_time() - core->last_time_eat > core->time_to_die)
		{
			core->exit = 1;
			sem_post(core->stop);
			message("%lu %d died\n", 1, core);
			break ;
		}
		if (core->count_of_eating == -1 || \
			core->count_of_meals < core->count_of_eating)
			meals = 1;
		if (!meals)
			core->exit = 1;
	}
}
