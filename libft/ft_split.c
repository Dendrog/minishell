/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:37:31 by jakim             #+#    #+#             */
/*   Updated: 2024/03/11 18:49:08 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	prepare(char ***result, int *count, char **ptr, char const *s)
{
	if (!s)
		return (-1);
	*result = (char **)malloc(sizeof (char *) * (ft_strlen(s) + 2));
	if (!(*result))
		return (-1);
	*ptr = (char *)malloc(sizeof (char) * (ft_strlen(s) + 2));
	if (!(*ptr))
	{
		free((*result));
		return (-1);
	}
	*count = 0;
	return (0);
}

static char	**ending(int i, char *ptr, char **result, int count)
{
	if (i)
	{
		ptr[i] = 0;
		result[count++] = ptr;
	}
	else
		free(ptr);
	result[count] = NULL;
	return (result);
}

static void	all_free(char **ptr, int len)
{
	while (len >= 0)
	{
		free(ptr[len - 1]);
		len--;
	}
	free(ptr);
}

static void	insert_result(int *i, char *ptr, char **result, int *count)
{
	if (*i)
	{
		ptr[*i] = 0;
		result[(*count)++] = ptr;
		*i = 0;
	}
	else
		free(ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	char	*ptr;
	int		i;
	int		count;

	if (prepare(&result, &count, &ptr, s))
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s == c)
		{
			insert_result(&i, ptr, result, &count);
			ptr = (char *)malloc(sizeof (char) * (ft_strlen(s++) + 2));
			if (!ptr)
			{
				all_free(result, count - 1);
				return (NULL);
			}
		}
		else
			ptr[i++] = *s++;
	}
	return (ending(i, ptr, result, count));
}
