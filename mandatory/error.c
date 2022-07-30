/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 21:06:29 by nabentay          #+#    #+#             */
/*   Updated: 2022/01/21 21:07:23 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_write_cmd_error(t_pipex pipex)
{
	int	i;

	i = ft_strlen(pipex.cmd_arg[0]);
	write(2, "command not found: \n", 19);
	write(2, pipex.cmd_arg[0], i);
	write(2, "\n", 1);
	ft_free(pipex.cmd_arg);
	ft_free(pipex.cmd_path);
	exit(10);
}

void	ft_exit_code(t_pipex *pipex)
{
	int	status;
	int	err;
	int	err2;

	err = 0;
	err = 2;
	waitpid(pipex->child, &status, 0);
	if (WIFEXITED(status))
	{
		err = WEXITSTATUS(status);
		if (err == 2)
			pipex->err = 1;
	}
	waitpid(pipex->child2, &status, 0);
	if (WIFEXITED(status))
	{
		err2 = WEXITSTATUS(status);
		if (err2 == 2)
			pipex->err = 1;
	}
	if (err == 10 || err2 == 10)
		pipex->err = 127;
}
