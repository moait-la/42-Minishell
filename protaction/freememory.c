/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freememory.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 00:19:44 by mochenna          #+#    #+#             */
/*   Updated: 2024/09/19 00:35:51 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

void	cleanlist(t_cmd **lst)
{
	t_cmd	*clean;

	while (*lst)
	{
		clean = *lst;
		*lst = (*lst)->next;
		freememory(clean->allcmd);
		freememory(clean->command);
		freememory(clean->redirection);
		free(clean);
	}
}

void	clean_env(t_env *env_lst)
{
	t_env	*temp;

	while (env_lst)
	{
		if (env_lst->key)
			free(env_lst->key);
		if (env_lst->value)
			free(env_lst->value);
		temp = env_lst;
		env_lst = env_lst->next;
		free(temp);
	}
}

void	freememory(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		free(s[i++]);
	free(s);
}

void	clean(t_minishell *clean, t_env *env_lst)
{
	(void)env_lst;
	free(clean->str);
	cleanlist(&clean->cmd);
}

bool	if_out(t_minishell *m, t_env *e, char *prt)
{
	char	**str;
	int		status;

	status = 0;
	str = splitline(m->read);
	if (!ft_strcmp(str[0], "exit"))
	{
		if (ft_exit(m, e, str, &status))
		{
			free(prt);
			free(m->read);
			freememory(str);
			exit(status);
		}
	}
	freememory(str);
	if (status == -1)
	{
		get_exitst(1, true);
		return (false);
	}
	return (true);
}
