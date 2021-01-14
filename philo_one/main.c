/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:18:16 by nelisabe          #+#    #+#             */
/*   Updated: 2021/01/14 17:36:37 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

//need to add unsigned long atoi

int		parse_arguments(char **argv, int argc, t_params *philosophers)
{
	int		index;

	if ((philosophers->number = ft_atoi(argv[0])) < 0)
		return (err_invalid_argument(argv[0]));
	if ((philosophers->time_to_die = ft_atoi(argv[1])) < 0)
		return (err_invalid_argument(argv[1]));
	if ((philosophers->time_to_eat = ft_atoi(argv[2])) < 0)
		return (err_invalid_argument(argv[2]));
	if ((philosophers->time_to_sleep = ft_atoi(argv[3])) < 0)
		return (err_invalid_argument(argv[3]));
	if (argc == 4)
		philosophers->count_of_eating = -1;
	else
		if ((philosophers->count_of_eating = ft_atoi(argv[4])) < 0)
			return (err_invalid_argument(argv[4]));
	if (!(philosophers->status = \
		(int*)malloc(sizeof(int) * philosophers->number)))
		return (err_malloc());
	index = -1;
	while (++index < philosophers->number)
		philosophers->status[index] = 0;
	return (0);
}

int		main(int argc, char **argv)
{
	t_params	philosophers;

	if (argc < 5 || argc > 6)
		return (err_arguments());
	if (parse_arguments(&argv[1], argc - 1, &philosophers))
		return (1);
	printf("%d\n", philosophers.number);
	printf("%d\n", philosophers.time_to_die);
	printf("%d\n", philosophers.time_to_eat);
	printf("%d\n", philosophers.time_to_sleep);
	printf("%d\n", philosophers.count_of_eating);
	int index;

	index = -1;
	while (++index < philosophers.number)
		printf("%d\n", philosophers.status[index]);
	return (0);
}
