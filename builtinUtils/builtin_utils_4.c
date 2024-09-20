/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:23:48 by moait-la          #+#    #+#             */
/*   Updated: 2024/09/14 17:27:01 by moait-la         ###   ########.fr       */
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
