/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:28:39 by jakim             #+#    #+#             */
/*   Updated: 2024/03/14 11:53:35 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*mem;
	char	*ptr;

	if (!s)
		return (NULL);
	mem = (char *)malloc(sizeof(char) * (len + 1));
	if (mem == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		*mem = 0;
		return (mem);
	}
	len = len + start;
	ptr = mem;
	while (start < len)
	{
		*ptr = s[start];
		if (*ptr == 0)
			return (mem);
		ptr++;
		start++;
	}
	*ptr = 0;
	return (mem);
}
