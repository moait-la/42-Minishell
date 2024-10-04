/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:54:12 by moait-la          #+#    #+#             */
/*   Updated: 2024/10/02 14:56:56 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

char	*ft_get_env_value(char *key, t_env *env_lst)
{
	while (env_lst)
	{
		if (!ft_strcmp(key, env_lst->key))
			return (env_lst->value);
		env_lst = env_lst->next;
	}
	return (NULL);
}

void	ft_handle_env_update(char *key, char *value, char *cmd, t_env *env_lst)
{
	if (ft_check_ifexists(key, env_lst) == 1)
	{
		if (!ft_equal_sign(cmd))
			ft_add_env(&env_lst, 0, key, value);
		else
			ft_add_env(&env_lst, 1, key, value);
	}
	else if (!ft_check_ifexists(key, env_lst) && !ft_equal_sign(cmd))
		ft_update_export_lst(env_lst, key, value);
	free_multi(key, value, NULL);
}

char	*update_value_to_new_value(char *value, char *key, t_env *env_lst)
{
	char	*temp_value;

	temp_value = value;
	if (!ft_check_ifexists(key, env_lst))
		value = ft_strjoin(ft_get_env_value(key, env_lst), value);
	else
		value = ft_strjoin(NULL, value);
	free(temp_value);
	return (value);
}

static void	ft_continue_export(t_cmd *cmd, t_env *env_lst)
{
	int		i;
	char	*value;
	char	*key;

	i = 0;
	while (cmd->command[++i])
	{
		if (is_valid_identifier(cmd->command[i], 0))
		{
			get_exitst(1, true);
			ft_putstr_fd("not a valid identifier\n", 2);
			continue ;
		}
		key = ft_get_key(cmd->command[i]);
		value = ft_get_value(cmd->command[i]);
		if (!ft_plus_check(cmd->command[i]))
			value = update_value_to_new_value(value, key, env_lst);
		ft_handle_env_update(key, value, cmd->command[i], env_lst);
	}
}

void	ft_export(t_cmd *cmd, t_env *env_lst)
{
	if (!cmd->command[1])
	{
		ft_sorted_envlst(cmd, env_lst, NULL);
		return ;
	}
	ft_continue_export(cmd, env_lst);
}
