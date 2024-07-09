/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:29:31 by jakim             #+#    #+#             */
/*   Updated: 2024/03/07 14:36:48 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*cp;
	int		i;

	if (!s1)
		return (0);
	while (*s1)
	{
		if (!ft_strchr(set, *s1))
			break ;
		s1++;
	}
	i = ft_strlen(s1) - 1;
	while (i > 0)
	{
		if (!ft_strchr(set, s1[i]))
			break ;
		i--;
	}
	cp = ft_substr(s1, 0, i + 1);
	if (!cp)
		return (NULL);
	return (cp);
}
