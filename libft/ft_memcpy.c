/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:24:17 by jakim             #+#    #+#             */
/*   Updated: 2024/03/07 14:37:11 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void	*save;

	if (!dest && !src)
		return (0);
	save = dest;
	while (n--)
		*(unsigned char *)(dest++) = *(const unsigned char *)(src++);
	return (save);
}
