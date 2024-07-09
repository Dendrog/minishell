/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:13:15 by jakim             #+#    #+#             */
/*   Updated: 2024/02/29 14:23:14 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*mem;
	char	*ptr;

	mem = NULL;
	mem = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (mem == NULL)
		return (mem);
	ptr = mem;
	while (*s)
		*(ptr++) = *(char *)(s++);
	*ptr = 0;
	return (mem);
}
