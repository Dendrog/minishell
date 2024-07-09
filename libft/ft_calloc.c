/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:59:55 by jakim             #+#    #+#             */
/*   Updated: 2024/03/06 16:37:42 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*mem;
	unsigned char	*ptr;
	size_t			i;

	mem = NULL;
	i = 0;
	mem = malloc(size * nmemb);
	if (mem == NULL)
		return ((void *)mem);
	ptr = (unsigned char *)mem;
	while (i < nmemb * size)
		ptr[i++] = 0;
	return ((void *)mem);
}
