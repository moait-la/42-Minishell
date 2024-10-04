/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:19:56 by moait-la          #+#    #+#             */
/*   Updated: 2024/10/02 14:58:23 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

void	ft_add_env(t_env **env_lst, int mybool, char *key, char *value)
{
	t_env	*new_node;
	t_env	*temp;

	new_node = (t_env *)ft_malloc(sizeof(t_env));
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->has_printed = 1;
	new_node->mybool = mybool;
	new_node->next = NULL;
	if (*env_lst == NULL)
		*env_lst = new_node;
	else
	{
		temp = *env_lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}

char	*ft_handle_point(t_cmd *cmd)
{
	char	*current_pwd;
	char	*dest;
	int		len;

	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return (perror("getcwd"), NULL);
	if (!ft_strcmp(cmd->command[1], "."))
		return (current_pwd);
	else if (!ft_strcmp(cmd->command[1], ".."))
	{
		len = ft_strlen(current_pwd) - ft_strlen(ft_strrchr(current_pwd, '/'));
		dest = ft_substr(current_pwd, 0, len);
		return (free(current_pwd), dest);
	}
	return (free(current_pwd), ft_strdup(cmd->command[1]));
}

int	is_valid_identifier(char *command, int mybool)
{
	int	j;

	j = -1;
	if (!ft_isalpha(command[0]) && command[0] != '_')
		return (1);
	while (command[++j])
	{
		if (command[j] == '=' && mybool == 0)
			return (0);
		else if (command[j] == '=' && mybool == 1)
			return (1);
		if (!ft_isalnum(command[j]) && command[j] != '_' && command[j] != '+')
			return (1);
		if (command[j] == '+' && command[j + 1] == '=')
			return (0);
		else if (command[j] == '+' && command[j + 1] != '=')
			return (1);
	}
	return (0);
}

int	ft_check_ifexists(char *key, t_env *env_lst)
{
	while (env_lst)
	{
		if (!ft_strcmp(key, env_lst->key))
			return (0);
		env_lst = env_lst->next;
	}
	return (1);
}

int	ft_equal_sign(char *cmd)
{
	while (*cmd)
	{
		if (*cmd == '=')
			return (0);
		cmd++;
	}
	return (1);
}
