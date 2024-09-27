/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:23:48 by moait-la          #+#    #+#             */
/*   Updated: 2024/09/24 21:24:18 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

void	ft_update_export_lst(t_env *env_lst, char *key, char *value)
{
	while (env_lst)
	{
		if (!ft_strcmp(env_lst->key, key))
		{
			free(env_lst->value);
			env_lst->value = ft_strdup(value);
			env_lst->mybool = 0;
			break ;
		}
		env_lst = env_lst->next;
	}
}

void	ft_reinit_has_printed(t_env *env_lst)
{
	while (env_lst)
	{
		env_lst->has_printed = 1;
		env_lst = env_lst->next;
	}
}

void	ft_sorted_envlst(t_cmd *cmd, t_env *env_lst, t_env	*smallest)
{
	t_env	*current;
	int		biggest_char;

	ft_reinit_has_printed(env_lst);
	while (1)
	{
		smallest = NULL;
		biggest_char = 127;
		current = env_lst;
		while (current)
		{
			if (current && current->key && current->key[0] < biggest_char
				&& current->has_printed != 0)
			{
				biggest_char = current->key[0];
				smallest = current;
			}
			current = current->next;
		}
		if (smallest == NULL)
			break ;
		smallest->has_printed = 0;
		if (smallest->mybool != 2)
			ft_print_export(cmd, smallest);
	}
}

char	*ft_curr_pwd_removed(char **dest, t_env *env_lst, t_cmd *cmd)
{
	char	*pwd;
	char	*tmp;

	pwd = NULL;
	tmp = NULL;
	while (env_lst)
	{
		if (!ft_strcmp(env_lst->key, "PWD"))
			pwd = ft_strdup(env_lst->value);
		if (!ft_strcmp(env_lst->key, "OLDPWD") && cmd->command[1])
			tmp = ft_strdup(env_lst->value);
		env_lst = env_lst->next;
	}
	*dest = tmp;
	if (cmd->command[1])
		perror("getcwd");
	return (pwd);
}
