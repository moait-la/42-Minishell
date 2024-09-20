/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 23:02:12 by moait-la          #+#    #+#             */
/*   Updated: 2024/09/10 22:08:04 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

void	*ft_get_home_user_env(char **home_path, char **user_env, t_env *env_lst)
{
	(*home_path) = ft_getenv("HOME", env_lst);
	if (!*home_path)
		return (ft_error("cd: HOME not set\n", NULL), NULL);
	(*user_env) = ft_getenv("USER", env_lst);
	if (!*user_env)
		return (ft_error("cd: USER not set\n", NULL), NULL);
	return ("1337");
}

static char	*ft_handle_tilde(t_cmd *cmd, t_env *env_lst)
{
	char	*user;
	char	*dest;
	char	*after_tilde;
	char	*home_path;
	char	*user_env;

	ft_get_home_user_env(&home_path, &user_env, env_lst);
	if (!home_path || !user_env)
		return (NULL);
	after_tilde = ft_strchr(cmd->command[1], '/');
	if (!after_tilde)
	{
		user = ft_strdup(cmd->command[1] + 1);
		if (!user)
			return (NULL);
		if (!ft_strcmp(user, user_env))
			dest = home_path;
		else
			return (free(user), cmd->command[1]);
		free(user);
	}
	else
		dest = ft_strjoin(home_path, after_tilde);
	return (dest);
}

static char	*ft_go_home(t_env *env_lst)
{
	char	*home_path;

	home_path = ft_getenv("HOME", env_lst);
	if (!home_path)
		return (ft_error("cd: HOME not set\n", NULL), NULL);
	return (ft_strdup(home_path));
}

static char	*ft_goto_path(t_cmd *cmd)
{
	char	*dest;
	char	*current_pwd;
	char	*temp;

	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return (get_exitst(1, true), perror("getcwd"), NULL);
	temp = NULL;
	if (!ft_check_ifroot(cmd->command[1]))
		return (free(current_pwd), ft_strdup("/"));
	else if (cmd->command[1][0] == '.')
		return (free(current_pwd), ft_handle_point(cmd));
	if (ft_strcmp(current_pwd, "/") != 0 && cmd->command[1][0] != '/')
		temp = ft_strjoin(current_pwd, "/");
	dest = ft_strjoin(temp, cmd->command[1]);
	free_multi(temp, current_pwd, NULL);
	return (dest);
}

void	ft_cd(t_cmd *cmd, t_env *env_lst)
{
	char	*dest;
	char	*current_pwd;
	char	*dest_path;

	dest = NULL;
	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return (get_exitst(1, true), perror("getcwd"));
	if (!cmd->command[1] || !ft_strcmp(cmd->command[1], "~"))
		dest = ft_go_home(env_lst);
	else if (!ft_strcmp(cmd->command[1], "-"))
		dest = ft_goto_prev_dir(env_lst);
	else if (cmd->command[1][0] == '~')
		dest = ft_handle_tilde(cmd, env_lst);
	else
		dest = ft_goto_path(cmd);
	if (!dest)
		return (free(current_pwd));
	if (chdir(dest) == -1)
		return (free_multi(dest, current_pwd, 0), ft_cd_perror("cd"));
	dest_path = getcwd(NULL, 0);
	if (!dest_path)
		return (ft_cd_perror(""));
	ft_update_env_lst(dest_path, current_pwd, env_lst);
	free_multi(dest, dest_path, current_pwd);
}
