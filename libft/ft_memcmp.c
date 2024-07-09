/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:19:30 by jakim             #+#    #+#             */
/*   Updated: 2024/02/28 22:32:09 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n)
	{
		if (*(unsigned char *)s1 != *(unsigned char *)s2)
			return ((int)(*(unsigned char *)s1 - *(unsigned char *)s2));
		s1++;
		s2++;
		n--;
	}
	return (0);
}
