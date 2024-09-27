/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 07:27:05 by moait-la          #+#    #+#             */
/*   Updated: 2024/09/24 21:24:03 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

void	ft_env(t_cmd *cmd, t_env *env)
{
	while (env)
	{
		if (!env->mybool || env->mybool == 2)
		{
			ft_putstr_fd(env->key, cmd->out);
			if (env->value != NULL)
			{
				ft_putstr_fd("=", cmd->out);
				ft_putstr_fd(env->value, cmd->out);
			}
			ft_putstr_fd("\n", cmd->out);
		}
		env = env->next;
	}
}

void	ft_pwd(t_cmd *cmd, t_env *env_lst, char *oldpwd, char *currentpwd)
{
	char	*pwd;
	t_env	*temp;

	pwd = getcwd(NULL, 0);
	temp = env_lst;
	if (!pwd)
	{
		while (temp)
		{
			if (!ft_strcmp(temp->key, "OLDPWD"))
				oldpwd = ft_strdup(temp->value);
			if (!ft_strcmp(temp->key, "PWD"))
				currentpwd = ft_strdup(temp->value);
			temp = temp->next;
		}
		if (chdir(oldpwd) == -1)
			return (free_multi(oldpwd, currentpwd, 0), ft_cd_perror("cd"));
		ft_update_env_lst(oldpwd, currentpwd, env_lst);
		free_multi(oldpwd, currentpwd, NULL);
		return (get_exitst(1, true), perror("getcwd"));
	}
	ft_putstr_fd(pwd, cmd->out);
	ft_putchar_fd('\n', cmd->out);
	free(pwd);
}

void	ft_print_export(t_cmd *cmd, t_env *smallest)
{
	ft_putstr_fd("declare -x ", cmd->out);
	ft_putstr_fd(smallest->key, cmd->out);
	if (smallest->value != NULL)
	{
		ft_putstr_fd("=", cmd->out);
		ft_putstr_fd("\"", cmd->out);
		ft_putstr_fd(smallest->value, cmd->out);
		ft_putstr_fd("\"", cmd->out);
	}
	ft_putstr_fd("\n", cmd->out);
}

int	ft_is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (0);
	return (1);
}

void	ft_execute_builtin(t_minishell *m, t_cmd *cmd, t_env **env_lst)
{
	if (!ft_strcmp(m->cmd->command[0], "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(m->cmd->command[0], "cd"))
		ft_cd(cmd, *env_lst);
	else if (!ft_strcmp(m->cmd->command[0], "env"))
		ft_env(cmd, *env_lst);
	else if (!ft_strcmp(m->cmd->command[0], "pwd"))
		ft_pwd(cmd, *env_lst, NULL, NULL);
	else if (!ft_strcmp(m->cmd->command[0], "unset"))
		ft_unset(cmd, env_lst);
	else if (!ft_strcmp(m->cmd->command[0], "export"))
		ft_export(cmd, *env_lst);
	else if (!ft_strcmp(m->cmd->command[0], "exit"))
		ft_exit(m, cmd);
}
