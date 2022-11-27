/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhizdahr <zhizdahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:45:40 by zhizdahr          #+#    #+#             */
/*   Updated: 2022/03/21 20:29:07 by zhizdahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_string_paths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
		i++;
	}
	return (ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5));
}

char	*path(char **envp, char *argv)
{
	char	**string_paths;
	char	*path;
	int		i;
	char	**comand;

	i = 0;
	string_paths = ft_split(get_string_paths(envp), ':');
	comand = ft_split(argv, ' ');
	while (string_paths[i])
	{
		path = ft_strjoin(string_paths[i], "/");
		path = ft_strjoin(path, comand[0]);
		if (!access(path, 0))
		{
			free_mat(comand);
			return (path);
		}
		i++;
	}
	free_mat(comand);
	free(path);
	return (0);
}

void	child(char **argv, int *pipefd, char **envp)
{
	int	in;

	in = open(argv[1], O_RDONLY);
	if (in < 0)
		exit(1);
	dup2(in, 0);
	dup2(pipefd[1], 1);
	close(pipefd[1]);
	close(pipefd[0]);
	close(in);
	execve(path(envp, argv[2]), ft_split(argv[2], ' '), envp);
}

void	parent(char **argv, int *pipefd, char **envp)
{
	int	out;

	wait(0);
	close(pipefd[1]);
	dup2(pipefd[0], 0);
	close(pipefd[0]);
	out = open(argv[4], O_RDWR | O_TRUNC | O_CREAT, 0777);
	dup2(out, 1);
	close(out);
	execve(path(envp, argv[3]), ft_split(argv[3], ' '), envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	if (argc != 5)
		return (0);
	if (pipe(pipefd))
	{
		perror("ERR_PIPE");
		return (EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (!pid)
		child(argv, pipefd, envp);
	else
		parent(argv, pipefd, envp);
	return (0);
}
