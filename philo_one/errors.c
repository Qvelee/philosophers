/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:38:20 by nelisabe          #+#    #+#             */
/*   Updated: 2021/01/14 17:34:05 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		err_malloc(void)
{
	printf("%s\n", ERR_MALLOC);
	return (1);
}

int		err_invalid_argument(char *argument)
{
	printf("%s %s\n", ERR_INV_ARGS, argument);
	return (1);
}

int		err_arguments(void)
{
	printf("%s\n", ERR_ARGS);
	return (1);
}
