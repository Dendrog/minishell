/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:50:15 by jakim             #+#    #+#             */
/*   Updated: 2024/03/14 11:58:08 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	sign(int n, int fd, char *str, int *flag)
{
	str[1] = 0;
	*flag = 0;
	if (n < 0)
	{
		write(fd, "-", 1);
		return (-1);
	}
	else
		return (1);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		base;
	int		flag;
	char	str[2];
	int		s;

	base = 1000000000;
	s = sign(n, fd, str, &flag);
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	while (base)
	{
		if (!(n / base) && flag == 1)
			write(fd, "0", 1);
		if (n / base)
		{
			flag = 1;
			str[0] = ((n / base) * s) + '0';
			write (fd, str, 1);
		}
		n = n % base;
		base = base / 10;
	}
}
