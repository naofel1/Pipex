/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:57:48 by nabentay          #+#    #+#             */
/*   Updated: 2022/07/30 22:36:24 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_cmd(char **path, char *cmd)
{
	char	*tmp;
	char	*res;

	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		res = ft_strjoin(tmp, cmd);
		free (tmp);
		if (access(res, 0) == 0)
			return (res);
		free (res);
		path++;
	}
	return (NULL);
}

void	ft_pipex_stdin(t_pipex pipex, char **av, char **env)
{
	pipex.cmd_arg = ft_split(av[2], ' ');
	pipex.cmd = get_cmd(pipex.cmd_path, pipex.cmd_arg[0]);
	if (!pipex.cmd)
		ft_write_cmd_error(pipex);
	if (dup2(pipex.pdes[1], STDOUT_FILENO) == -1)
	{
		ft_free(pipex.cmd_path);
		ft_free(pipex.cmd_arg);
		free(pipex.cmd);
		exit(2);
	}
	close(pipex.pdes[0]);
	if (dup2(pipex.fd_in, STDIN_FILENO) == -1)
	{
		ft_free(pipex.cmd_path);
		ft_free(pipex.cmd_arg);
		free(pipex.cmd);
		exit(2);
	}
	if (execve(pipex.cmd, pipex.cmd_arg, env) == -1)
		perror("execve failed");
}

void	ft_pipex_stdout(t_pipex pipex, char **av, char **env)
{
	pipex.cmd_arg = ft_split(av[3], ' ');
	pipex.cmd = get_cmd(pipex.cmd_path, pipex.cmd_arg[0]);
	if (!pipex.cmd)
		ft_write_cmd_error(pipex);
	if (dup2(pipex.pdes[0], STDIN_FILENO) == -1)
	{
		ft_free(pipex.cmd_path);
		ft_free(pipex.cmd_arg);
		free(pipex.cmd);
		exit(2);
	}
	close(pipex.pdes[1]);
	if (dup2(pipex.fd_out, STDOUT_FILENO) == -1)
	{
		ft_free(pipex.cmd_path);
		ft_free(pipex.cmd_arg);
		free(pipex.cmd);
		exit(2);
	}
	if (execve(pipex.cmd, pipex.cmd_arg, env) == -1)
		perror("execve failed");
}

void	run_pipe(char **av, char **env)
{
	t_pipex	pipex;

	pipex.err = 0;
	pipex.fd_in = open(av[1], O_RDONLY);
	pipex.fd_out = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (pipex.fd_in == -1 || pipex.fd_out == -1)
		perror("Error");
	if (pipe(pipex.pdes) < 0)
		perror("Pipe");
	pipex.path = ft_find_path(env);
	pipex.cmd_path = ft_split(pipex.path, ':');
	pipex.child = fork();
	if (pipex.child == 0)
		ft_pipex_stdin(pipex, av, env);
	pipex.child2 = fork();
	if (pipex.child2 == 0)
		ft_pipex_stdout(pipex, av, env);
	close(pipex.pdes[0]);
	close(pipex.pdes[1]);
	ft_exit_code(&pipex);
	ft_free(pipex.cmd_path);
	exit(pipex.err);
}

int	main(int ac, char **av, char **env)
{
	if (ac == 5)
	{
		if (*env == NULL)
		{
			write(2, "Missing environment\n", 20);
			return (1);
		}
		run_pipe(av, env);
		return (0);
	}
	else
		write(2, "Error\n", 6);
	return (1);
}
