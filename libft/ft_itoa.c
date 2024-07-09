/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:37:50 by jakim             #+#    #+#             */
/*   Updated: 2024/03/11 18:28:55 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(int n, char *result, int *base, int *set)
{
	if (n == 0)
	{
		result[0] = '0';
		*base = 0;
		return (1);
	}
	if (n < 0)
	{
		result[0] = '-';
		*base = *base * -1;
		*set = 1;
		return (1);
	}
	return (0);
}

static int	calc_size(int n)
{
	int	i;

	i = 2;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		i;
	int		base;
	int		set;

	base = 1000000000;
	set = 0;
	result = (char *)malloc(sizeof(char) * calc_size(n));
	if (!result)
		return (NULL);
	i = check(n, result, &base, &set);
	while (base)
	{
		if (n / base)
		{
			result[i++] = (n / base) + '0';
			n = n % base;
		}
		else
			if (i > set)
				result[i++] = '0';
		base = base / 10;
	}
	result[i] = 0;
	return (result);
}
