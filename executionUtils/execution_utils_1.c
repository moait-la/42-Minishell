/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 00:37:04 by moait-la          #+#    #+#             */
/*   Updated: 2024/09/19 19:43:51 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

int	ft_get_file_fd(int mybool, char *name)
{
	int	fd;

	fd = 0;
	if (mybool == 1)
		fd = open(name, O_RDONLY);
	else if (mybool == 2)
		fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	else if (mybool == 3)
		fd = open(name, O_CREAT | O_WRONLY | O_APPEND, 0666);
	return (fd);
}

int	open_file(char *name, int mybool, t_minishell *t_mini)
{
	int	fd;

	fd = ft_get_file_fd(mybool, name);
	if (fd == -1 && mybool == 1)
	{
		if (!t_mini->allpip)
			return (ft_openfile_error());
		fd = open("/dev/null", O_RDONLY, 0666);
		if (fd == -1)
			return (ft_openfile_error());
		putstr_fd(2, strerror(errno), "\n");
		return (get_exitst(1, true), fd);
	}
	else if (fd == -1 && (mybool == 2 || mybool == 3))
	{
		if (!t_mini->allpip)
			return (ft_openfile_error());
		fd = open("/dev/null", O_RDONLY, 0666);
		if (fd == -1)
			return (ft_openfile_error());
		putstr_fd(2, strerror(errno), "\n");
		return (get_exitst(1, true), fd);
	}
	return (fd);
}

static char	*ft_chose_path(t_env *env_lst, t_minishell *t_mini)
{
	char	*path;

	path = NULL;
	if (t_mini->env_passed == 1)
		return (ft_strdup(DEFAULT_PATH));
	path = ft_getenv("PATH", env_lst);
	if (!path)
		return (ft_strdup("not set"));
	return (ft_strdup(path));
}

static char	*ft_join_cmd_with_path(char *cmd, char **all_paths)
{
	char	*path;
	char	*cmd_path;
	int		i;

	i = -1;
	while (all_paths[++i] != NULL)
	{
		path = ft_strjoin(all_paths[i], "/");
		cmd_path = ft_strjoin(path, cmd);
		free(path);
		if (access(cmd_path, X_OK) == 0)
			return (ft_free(all_paths), cmd_path);
		if (all_paths[i + 1] != NULL)
			free(cmd_path);
	}
	free(cmd_path);
	return (NULL);
}

char	*ft_get_path(char *cmd, t_env *env_lst, t_minishell *t_mini)
{
	char	*path;
	char	**all_paths;
	char	*cmd_path;

	if (!cmd || !ft_exec_file_check(cmd))
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	else
	{
		path = ft_chose_path(env_lst, t_mini);
		all_paths = ft_split(path, ':');
		free(path);
		cmd_path = ft_join_cmd_with_path(cmd, all_paths);
		if (cmd_path)
			return (cmd_path);
	}
	ft_free(all_paths);
	free(cmd_path);
	ft_putstr_fd(NOT_FOUND, 2);
	return (get_exitst(127, true), NULL);
}
