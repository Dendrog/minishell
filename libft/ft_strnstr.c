/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:33:05 by jakim             #+#    #+#             */
/*   Updated: 2024/03/14 11:43:35 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (!*little)
		return ((char *)big);
	while (*big && len > 0)
	{
		i = 0;
		while (big[i] == little[i] && i < len)
		{
			i++;
			if (little[i] == 0)
				return ((char *)big);
		}
		big++;
		len--;
	}
	return (NULL);
}
