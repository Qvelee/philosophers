/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 19:32:41 by nelisabe          #+#    #+#             */
/*   Updated: 2021/01/14 17:16:31 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static	void	ff_lines(long *sindex, long *number, long *copy)
{
	if (*number == 0)
		*sindex = 0;
	if (*number < 0)
		(*sindex)++;
	*copy = *number;
	if (*number < 0)
		*copy = (*number) * -1;
	while (*copy > 0)
	{
		(*copy) /= 10;
		(*sindex)++;
	}
}

char			*ft_itoa(int num)
{
	char *str;
	long copy;
	long sindex;
	long number;

	number = (long)num;
	sindex = -1;
	ff_lines(&sindex, &number, &copy);
	str = (char*)malloc(sizeof(char) * sindex + 2);
	if (!(str))
		return (NULL);
	if (number < 0)
		str[0] = '-';
	str[sindex + 1] = '\0';
	while (sindex >= 0 && str[sindex] != '-')
	{
		if (number < 0)
			number *= -1;
		str[sindex--] = number % 10 + '0';
		number /= 10;
	}
	return (str);
}
