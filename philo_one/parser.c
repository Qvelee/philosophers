/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:36:43 by nelisabe          #+#    #+#             */
/*   Updated: 2021/01/26 18:19:06 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		get_one_param(char *argument, long *save_to)
{
	int		index;

	index = -1;
	while (argument[++index])
		if (!ft_isdigit(argument[index]))
			return (err_invalid_argument(argument));
	*save_to = ft_atol(argument);
	return (0);
}

int		parse(int argc, char **argv, t_core *core)
{
	if (argc < 5 || argc > 6)
		return (err_arguments());
	if (get_one_param(argv[1], (long *)&core->count_of_philos))
		return (1);
	if (get_one_param(argv[2], (long *)&core->time_to_die))
		return (1);
	if (get_one_param(argv[3], (long *)&core->time_to_eat))
		return (1);
	if (get_one_param(argv[4], (long *)&core->time_to_sleep))
		return (1);
	if (argc == 6 && get_one_param(argv[5], (long *)&core->count_of_eating))
		return (1);
	return (0);
}
