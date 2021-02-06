/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:18:16 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/06 13:32:00 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
