/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:19:25 by moait-la          #+#    #+#             */
/*   Updated: 2024/10/02 14:57:05 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

void	free_multi(void *adrs1, void *adrs2, void *adrs3)
{
	if (adrs1)
		free(adrs1);
	if (adrs2)
		free(adrs2);
	if (adrs3)
		free(adrs3);
}

void	ft_unset_from_lst(char *key, t_env **env_lst)
{
	t_env	*temp;
	t_env	*prev;

	temp = *env_lst;
	while (temp)
	{
		if (!ft_strcmp(key, temp->key))
		{
			if (temp == *env_lst)
			{
				*env_lst = temp->next;
			}
			else
				prev->next = temp->next;
			free_multi(temp->value, temp->key, NULL);
			free(temp);
			temp = NULL;
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}

void	ft_unset_env(t_cmd *cmd, t_env **env_lst)
{
	t_env	*temp;
	char	*key;
	int		i;

	i = 0;
	while (cmd->command[++i])
	{
		if (is_valid_identifier(cmd->command[i], 1))
		{
			get_exitst(1, true);
			ft_putstr_fd("not a valid identifier\n", 2);
			continue ;
		}
		temp = *env_lst;
		key = ft_get_key(cmd->command[i]);
		while (temp)
		{
			if (!ft_check_ifexists(key, *env_lst))
				ft_unset_from_lst(key, env_lst);
			temp = temp->next;
		}
		free(key);
	}
}

void	ft_unset(t_cmd *cmd, t_env **env_lst)
{
	if (!cmd->command[1])
		return ;
	ft_unset_env(cmd, env_lst);
}
