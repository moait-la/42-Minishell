/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 07:27:05 by moait-la          #+#    #+#             */
/*   Updated: 2024/09/10 22:07:45 by moait-la         ###   ########.fr       */
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

void	ft_pwd(t_cmd *cmd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (get_exitst(1, true), perror("getcwd"));
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
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env"))
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
		ft_pwd(cmd);
	else if (!ft_strcmp(m->cmd->command[0], "unset"))
		ft_unset(cmd, env_lst);
	else if (!ft_strcmp(m->cmd->command[0], "export"))
		ft_export(cmd, *env_lst);
	if (cmd->out != 1)
		close(cmd->out);
}
