/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:55:39 by nabentay          #+#    #+#             */
/*   Updated: 2022/01/21 21:06:16 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_pipex {
	int		fd_in;
	int		err;
	int		fd_out;
	int		pdes[2];
	char	*path;
	char	**cmd_path;
	char	**cmd_arg;
	char	*cmd;
	pid_t	child;
	pid_t	child2;
}				t_pipex;

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(const char *s, char c);
size_t	ft_strlen(const char *str);
char	*ft_itoa(int n);
void	ft_free(char **str);
void	ft_write_cmd_error(t_pipex pipex);
void	ft_exit_code(t_pipex *pipex);
char	*ft_find_path(char **env);

#endif
