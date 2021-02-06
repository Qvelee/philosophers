/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:38:20 by nelisabe          #+#    #+#             */
/*   Updated: 2021/02/06 13:45:27 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		err_philos(t_core *core)
{
	destoy_allocated(core);
	return (1);
}

int		err_message(char *message)
{
	printf("%s: %s\n", ERR_SMTNWR, message);
	return (1);
}

int		err_malloc(void)
{
	printf("%s\n", ERR_MALLOC);
	return (1);
}

int		err_invalid_argument(char *argument)
{
	printf("%s '%s'\n", ERR_INV_ARGS, argument);
	return (1);
}

int		err_arguments(void)
{
	printf("%s\n", ERR_ARGS);
	return (1);
}
