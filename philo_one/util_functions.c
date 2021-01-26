/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:37:35 by nelisabe          #+#    #+#             */
/*   Updated: 2021/01/26 17:23:42 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		free_memory(int ret, void *mem_1, void *mem_2, void *mem_3)
{
	if (mem_1)
		free(mem_1);
	if (mem_2)
		free(mem_2);
	if (mem_3)
		free(mem_3);
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
