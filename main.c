/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:12:13 by jakim             #+#    #+#             */
/*   Updated: 2024/07/09 21:28:47 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<readline/readline.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include "libft/libft.h"
#include <errno.h>

void	error_end(int er)
{
	errno = er;
	if (errno == EOPNOTSUPP)
	{
		perror("command not found");
		exit(127);
	}
	perror("Error");
	exit(1);
}

static void	check_err(int n, int tar, int status, int type)
{
	if (type)
	{
		if (n == tar)
			error_end(status);
	}
	else if (type == 0)
	{
		if (n != tar)
			error_end(status);
	}
	else
	{
		if (n < tar)
			error_end(status);
	}
}

char	*ft_strdup2(const char *s, int len)
{
	char	*mem;
	char	*ptr;
	char	*f;

	mem = NULL;
	mem = (char *)malloc(sizeof(char) * (len + 1));
	if (mem == NULL)
		return (mem);
	if (!s)
	{
		mem[0] = 0;
		return (mem);
	}
	f = (char *)s;
	ptr = mem;
	while (*s)
		*(ptr++) = *(char *)(s++);
	*ptr = 0;
	free(f);
	return (mem);
}

char	**extract_path(char *envp[])
{
	char	**tmp;
	char	**re;

	tmp = NULL;
	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
			break ;
		envp++;
	}
	if (*envp)
	{
		tmp = ft_split((*envp) + 5, ':');
		re = tmp;
		while (*re)
		{
			ft_strlcat(*re, "/", 999);
			re++;
		}
	}
	return (tmp);
}

char	**make_arg(char *argv)
{
	char	**re;
	char	*tmp;

	re = ft_split(argv, ' ');
	if (!re)
		return (NULL);
	tmp = ft_strdup2(re[0], 100);
	re[0] = tmp;
	return (re);
}

void	f_all(char **target)
{
	char	**tmp;

	tmp = target;
	while (*target)
	{
		free(*target);
		target++;
	}
	free(tmp);
}

void	access_test(char *path, char **ar, char *envp[], int *flag)
{
	char	*tmp;

	tmp = ft_strjoin(path, ar[0]);
	if (!access(tmp, X_OK))
	{
		free(ar[0]);
		ar[0] = ft_strdup(tmp);
		*flag = execve(tmp, ar, envp);
	}
	free(tmp);
}

int	execute(char *argv, char *envp[])
{
	char	**path;
	char	**ar;
	int		flag;
	int		i;

	i = 0;
	flag = -1;
	path = extract_path(envp);
	ar = make_arg(argv);
	while (path[i])
	{
		access_test(path[i], ar, envp, &flag);
		i++;
	}
	access_test("", ar, envp, &flag);
	f_all(ar);
	f_all(path);
	return (flag);
}

char	*extract_name(char *envp[])
{
	char	*tmp;
	char	**re;

	tmp = NULL;
	while (*envp)
	{
		if (!ft_strncmp(*envp, "USER=", 5))
			break ;
		envp++;
	}
	tmp = (*envp);
	return (tmp+5);
}

char	*extract_location(char *envp[])
{
	char	*tmp;
	char	**re;

	tmp = NULL;
	while (*envp)
	{
		if (!ft_strncmp(*envp, "SESSION_MANAGER=", 16))
			break ;
		envp++;
	}
	tmp = (*envp);
	return (ft_substr(tmp, 22, ft_strchr(tmp, '.') - tmp - 22));
}

int main(int argc, char *argv[], char *envp[])
{
	char	*cin;
	pid_t	pid;
	int	status;
	char	*cwd;
	while (1)
	{
		cwd = getcwd(NULL, BUFSIZ);
		cwd = ft_strjoin(cwd, "$ ");
		cwd = ft_strjoin(":", cwd);
		cwd = ft_strjoin(extract_location(envp), cwd);
		cwd = ft_strjoin("@", cwd);
		cwd = ft_strjoin(extract_name(envp), cwd);
		//free 해야함
		pid = fork();
		if (pid > 0)
			wait(&status);
		else
		{
			while (1)
			{
				cin = readline(cwd);
				check_err(execute(cin, envp), -1, EOPNOTSUPP, 1);
			}
		}
	}
}