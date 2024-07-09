/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:15:18 by jakim             #+#    #+#             */
/*   Updated: 2024/03/14 11:39:18 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int		count;
	char	*tmp;

	tmp = (char *)src;
	count = 0;
	while (*(tmp++))
		count++;
	if (size == 0)
		return ((size_t)count);
	while (size-- > 0)
	{
		*dst = *src;
		if (!*src)
			return ((size_t)count);
		dst++;
		src++;
	}
	*(--dst) = 0;
	return ((size_t)count);
}
