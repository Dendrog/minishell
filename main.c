/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:12:13 by jakim             #+#    #+#             */
/*   Updated: 2024/08/20 18:47:48 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<readline/readline.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include "libft/libft.h"
#include <errno.h>
#include <termios.h>
#include <readline/history.h>

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

char	*extract_home(char *envp[])
{
	char	*tmp;
	char	**re;

	tmp = NULL;
	while (*envp)
	{
		if (!ft_strncmp(*envp, "HOME=", 5))
			break ;
		envp++;
	}
	tmp = (*envp);
	return (tmp+5);
}

void	sg(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		printf("^C\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGTERM)
	{
		printf("exit\n");
		exit(0);
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
}

void	input_sig(struct termios *old)
{
	tcgetattr(0, old);
	old->c_lflag &= ~(512);
	tcsetattr(0, TCSANOW, old);
	signal(SIGINT, sg);
	signal(SIGTERM, sg);
	signal(SIGQUIT, sg);
}

void	end_sig(struct termios *old)
{
	tcgetattr(0, old);
	old->c_lflag |= 512;
	tcsetattr(0, TCSANOW, old);
	signal(SIGINT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	all_free(char **ptr)
{
	while (*ptr != NULL)
	{
		free(*ptr);
		ptr++;
	}
	free(ptr);
}

char **update_envp(char **envp, int type, char *new)
{
	int	i;
	char	**ptr;

	i = 0;
	ptr = envp;
	while (*ptr != NULL)
	{
		i++;
		ptr++;
	}
	ptr = (char **)malloc((i + 5) * sizeof(char *));
	i = 0;
	while (envp[i] != NULL)
	{
		ptr[i] = ft_strdup(envp[i]);
		i++;
	}
	ptr[i++] = new;
	ptr[i] = NULL;
	if (type == 1)
		all_free(envp);
	return (ptr);
}

int	double_ptr_size(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
		i++;
	return (i);
}

int	search_env(char **envp, char *name)
{
	int	i;
	char	*re;

	i = 0;
	if (ft_strchr(name, '='))
		re = ft_substr(name, 0, ft_strchr(name, '=') - name);
	else
		re = name;
	while (*envp)
	{
		if (!ft_strncmp(*envp, re, ft_strlen(re)))
			break ;
		envp++;
		i++;
	}
	return (i);
}

int	is_validname(char *ptr)
{
	while (*ptr && *ptr != '=')
	{
		if (!ft_isalnum(*ptr) && *ptr != '_')
			return (0);
		ptr++;
	}
	return (1);
}

int	env_validate(char *ptr)
{
	if ((ft_isalpha(*ptr) || *ptr == '_') && is_validname(ptr))
	{
		if (ft_strchr(ptr, '='))
		{
			if ((ft_strchr(ptr, '=') + 1)[0] == '\0')
				return (1);
			if (ft_strchr(ptr, '=') != ft_strrchr(ptr, '='))
				return (1);
			return (1);
		}
		else
			return (0);
	}
	else
		return (-1);
}

char *set_env(char *name, int flag, char ***envp)
{
	int	i;
	
	if (flag < 0)
		return (name);
	else
	{
		i = search_env(*envp, name);
		if ((*envp)[i] != NULL)
		{
			if (!ft_strchr(name, '='))
				return (NULL);
			free((*envp)[i]);
			(*envp)[i] =  name;
		}
		else
			*envp = update_envp(*envp, 0, name);
	}
	return (NULL);
}

void	print_envp(char **envp, int flag)
{
	while (*envp != NULL)
	{
		if (flag == 1)
		{
			if (env_validate(*envp))
			{
				ft_putstr_fd("declare -x ", 1);
				write(1, *envp, ft_strchr(*envp, '=') - *envp);
				write(1, "=\"", 2);
				ft_putstr_fd(ft_strchr(*envp, '=') + 1, 1);
				write(1, "\"\n", 2);
			}
			else
				printf("declare -x %s\n", *envp);
		}
		else
		{
			if (env_validate(*envp))
				printf("%s\n", *envp);
		}
		envp++;
	}
}

void	ft_export(char **ptr, char ***envp)
{
	int	i;
	int	flag;
	char	*rax;

	i = 1;
	flag = 0;
	while (ptr[i] != NULL)
	{
		rax = set_env(ptr[i], env_validate(ptr[i]), envp);
		if (flag == 0 && rax != NULL)
		{
			printf("minishell: export: `%s': not a valid identifier\n", rax);
			flag = 1;
		}
		i++;
	}
}

int main(int argc, char *argv[], char *env[])
{
	char	*cin;
	pid_t	pid;
	int	status;
	char	*cwd;
	char	*pwd;
	char	*tmp_pwd;
	char	**cd;
	char	**cd_path;
	char	**envp;
	int i;
	struct termios	old;

	envp = update_envp(env, 0, NULL);
	while (1)
	{
		pwd = getcwd(NULL, BUFSIZ);
		if (!ft_strncmp(pwd, extract_home(envp), ft_strlen(extract_home(envp))))
			{
				cwd = pwd + ft_strlen(extract_home(envp));
				cwd = ft_strjoin("~", cwd);
			}
		else
			cwd = pwd;
		cwd = ft_strjoin(cwd, "$ ");
		cwd = ft_strjoin(":", cwd);
		cwd = ft_strjoin(extract_location(envp), cwd);
		cwd = ft_strjoin("@", cwd);
		cwd = ft_strjoin(extract_name(envp), cwd);
		//free 해야함
		input_sig(&old);
		cin = readline(cwd);
		end_sig(&old);
		if (!cin)
		{
			printf("exit\n");
			exit(0);
		}
		add_history(cin);
		if (cin[0] == 'c' && cin[1] == 'd' && (cin[2] == ' ' || cin[2] == '\0'))//!ft_strncmp(cin, "cd", 4))
		{
			tmp_pwd = ft_strdup(pwd);
			cd = ft_split(cin, ' '); //free
			if (cd[1] == NULL)
			{
				free(tmp_pwd);
				tmp_pwd = ft_strdup(extract_home(envp));
			}
			else if(cd[2] != NULL)
				printf("minishell: cd: too many arguments\n"); //표준에러로 바꾸는게 날거같긴함
			else
			{
				if(!ft_strncmp(cd[1], "/", 1)) //boom
				{
					free(tmp_pwd);
					tmp_pwd = ft_strdup("/");
				}
				i = 0;
				cd_path = ft_split(cd[1], '/');
				while (cd_path[i] != NULL)
				{
					if (i == 0 && !ft_strncmp(cd_path[i], "~", 4))
					{
						free(tmp_pwd);
						tmp_pwd = ft_strdup(extract_home(envp)); // free
					}
					else
					{
						if (!ft_strncmp(cd_path[i], "..", 5))
						{
							if (ft_strrchr(tmp_pwd, '/') == tmp_pwd)
								*(ft_strrchr(tmp_pwd, '/') + 1) = '\0';
							else
								*(ft_strrchr(tmp_pwd, '/')) = '\0';
						}
						else
						{
							tmp_pwd = ft_strjoin(tmp_pwd, "/"); //free 해야함
							tmp_pwd = ft_strjoin(tmp_pwd, cd_path[i]); //free 해야함
						}
					}
					i++;
				}
			}
			if (chdir(tmp_pwd) == -1)
				printf("minishell: cd: %s: No such file or directory\n", cd[1]);
		}
		else if(!ft_strncmp(cin, "export ",7) || !ft_strncmp(cin, "export", 8))
		{
			cd = ft_split(cin, ' ');
			if (cd[1] == NULL)
				print_envp(envp, 1);
			else
				ft_export(cd, &envp);
		}
		else if(!ft_strncmp(cin, "env",5) || !ft_strncmp(cin, "env ", 4))
			print_envp(envp, 0);
		else
		{
			pid = fork();
			if (pid > 0)
				wait(&status);
			else
				check_err(execute(cin, envp), -1, EOPNOTSUPP, 1);
		}
	}
}