/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:18:15 by jakim             #+#    #+#             */
/*   Updated: 2024/03/14 11:33:42 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	size_set(size_t *size, char **dst)
{
	while (*size && **dst)
	{
		(*dst)++;
		(*size)--;
	}
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	temp;
	size_t	dstlen;
	size_t	srclen;

	temp = size;
	srclen = ft_strlen(src);
	if (!size)
		return (srclen + size);
	dstlen = ft_strlen(dst);
	size_set(&size, &dst);
	if (!size)
		return (srclen + temp);
	while (size && *src)
	{
		*(dst++) = *(src++);
		size--;
	}
	if (!size)
		*(dst - sizeof(char)) = 0;
	else
		*dst = 0;
	return (dstlen + srclen);
}
