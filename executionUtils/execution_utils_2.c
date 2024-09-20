/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 03:19:24 by moait-la          #+#    #+#             */
/*   Updated: 2024/09/11 18:23:24 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

char	*ft_getenv(char *key, t_env *env_lst)
{
	while (env_lst)
	{
		if (!ft_strcmp(key, env_lst->key))
			return (env_lst->value);
		env_lst = env_lst->next;
	}
	return (NULL);
}

static void	ft_update_value(char **command, t_env **env_lst)
{
	t_env	*temp;
	int		i;

	i = -1;
	while (command[++i])
		if (!command[i + 1])
			break ;
	temp = *env_lst;
	while (temp)
	{
		if (!ft_strcmp(temp->key, "_"))
		{
			free(temp->value);
			temp->value = ft_strdup(command[i]);
		}
		temp = temp->next;
	}
}

void	ft_update_udnerscore(char **command, t_env **env_lst)
{
	t_env	*temp;
	char	*check;
	int		i;

	i = -1;
	temp = *env_lst;
	check = ft_getenv("_", *env_lst);
	if (!check)
	{
		if (!(*env_lst))
			*env_lst = ft_create_node("_");
		else
		{
			while (temp->next)
				temp = temp->next;
			temp->next = ft_create_node("_");
		}
	}
	ft_update_value(command, env_lst);
}

void	dup2_and_close(int cpy_dup, int fd)
{
	dup2(cpy_dup, 0);
	close(cpy_dup);
	close(fd);
}
