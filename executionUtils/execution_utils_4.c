/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:27:49 by moait-la          #+#    #+#             */
/*   Updated: 2024/09/14 18:44:12 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

char	*ft_get_value(char *cmd)
{
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(cmd);
	while (cmd[++i])
	{
		if (cmd[i] == '=')
			return (ft_substr(cmd, i + 1, len));
	}
	return (NULL);
}

char	*ft_get_key(char *cmd)
{
	int		i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '=')
		{
			if (cmd[i - 1] == '+')
				return (ft_substr(cmd, 0, i - 1));
			return (ft_substr(cmd, 0, i));
		}
	}
	return (ft_strdup(cmd));
}

int	ft_skip_env(char *envp, int i)
{
	char	*key;

	key = ft_get_key(envp);
	if (!ft_strcmp(key, "OLDPWD") || !ft_strcmp(key, "_"))
		i++;
	free(key);
	return (i);
}

void	ft_init_start_data(t_minishell *t_mini)
{
	t_cmd	*tmp;

	tmp = t_mini->cmd;
	while (tmp)
	{
		tmp->infile_not_valid = 1;
		tmp->in = 0;
		tmp->out = 1;
		tmp = tmp->next;
	}
}

int	ft_arguments_nbr(char **command)
{
	int	i;

	i = 0;
	while (command[i])
		i++;
	return (i);
}
