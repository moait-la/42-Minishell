/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_envlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 00:37:35 by moait-la          #+#    #+#             */
/*   Updated: 2024/09/11 16:46:57 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

static char	**env_list_to_array(t_env *env_lst, char **envp)
{
	t_env	*temp;
	char	*join;
	char	*temp_2;
	int		count;

	temp = env_lst;
	count = 0;
	while (temp)
	{
		temp = temp->next;
		count++;
	}
	envp = (char **)ft_malloc(sizeof(char *) * (count + 1));
	count = 0;
	while (env_lst)
	{
		temp_2 = ft_strjoin(env_lst->key, "=");
		join = ft_strjoin(temp_2, env_lst->value);
		envp[count] = ft_strdup(join);
		free_multi(temp_2, join, NULL);
		count++;
		env_lst = env_lst->next;
	}
	envp[count] = NULL;
	return (envp);
}

t_env	*ft_create_node(char *env)
{
	t_env	*node;
	int		shlvl;
	int		mybool;

	mybool = 0;
	if (!*env)
		return (NULL);
	node = (t_env *)ft_malloc(sizeof(t_env));
	node->key = ft_get_key(env);
	node->value = ft_get_value(env);
	if (!ft_strcmp(node->key, "_"))
		mybool = 2;
	else if (!ft_strcmp(node->key, "SHLVL"))
	{
		shlvl = ft_atoi(node->value);
		shlvl += 1;
		free(node->value);
		node->value = ft_itoa(shlvl);
	}
	node->mybool = mybool;
	node->has_printed = mybool;
	node->next = NULL;
	return (node);
}

static t_env	*ft_add_mandatory_env(t_minishell *t_mini)
{
	t_env	*env_lst;
	char	*temp;
	char	*current_path;

	t_mini->env_passed = 1;
	current_path = getcwd(NULL, 0);
	if (!current_path)
		return (perror("getcwd"), get_exitst(1, true), NULL);
	temp = ft_strjoin("PWD=", current_path);
	free(current_path);
	env_lst = ft_create_node(temp);
	free(temp);
	env_lst->next = ft_create_node("_=");
	env_lst->next->next = ft_create_node("SHLVL=0");
	return (env_lst);
}

t_env	*ft_parse_envp(char **envp, t_minishell *t_mini, int i)
{
	t_env	*temp;
	t_env	*env_lst;

	env_lst = NULL;
	if (*envp)
	{
		while (envp[++i])
		{
			if (!env_lst)
			{
				env_lst = ft_create_node(envp[0]);
				temp = env_lst;
			}
			i = ft_skip_env(envp[i], i);
			if (!envp[i])
				break ;
			temp->next = ft_create_node(envp[i]);
			temp = temp->next;
			temp->next = NULL;
		}
	}
	else
		env_lst = ft_add_mandatory_env(t_mini);
	t_mini->envp = env_list_to_array(env_lst, NULL);
	return (env_lst);
}
