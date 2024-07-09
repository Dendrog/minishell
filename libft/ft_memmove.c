/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:21:03 by jakim             #+#    #+#             */
/*   Updated: 2024/03/06 13:37:48 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void			*save;
	int				count;

	if (!dest && !src)
		return (0);
	save = dest;
	count = 1;
	if (dest > src)
	{
		count = -1;
		dest += n - 1;
		src += n - 1;
	}
	while (n--)
	{
		*(unsigned char *)dest = *(const unsigned char *)src;
		dest += sizeof(unsigned char) * count;
		src += sizeof(unsigned char) * count;
	}
	return (save);
}
