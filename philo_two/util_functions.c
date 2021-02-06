/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:37:35 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/06 13:45:09 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		mssleep(size_t msseconds)
{
	if (usleep(msseconds * 1000))
		return (-1);
	return (0);
}

int		get_time(void)
{
	struct	timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int		free_memory(int ret, void *mem_1, void *mem_2)
{
	if (mem_1)
		free(mem_1);
	if (mem_2)
		free(mem_2);
	return (ret);
}

int		ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

long	ft_atol(const char *str)
{
	long	result;
	int 	index;
	int 	minus;

	index = 0;
	result = 0;
	minus = 1;
	while (str[index] == ' ' || (str[index] <= '\r' && str[index] >= '\t'))
		index++;
	if (str[index] == '+' || str[index] == '-')
		if (str[index++] == '-')
			minus = -1;
	while (str[index] >= '0' && str[index] <= '9')
		result = result * 10 + (str[index++] - '0');
	return (result * minus);
}
