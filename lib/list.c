/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 00:38:53 by mochenna          #+#    #+#             */
/*   Updated: 2024/09/11 17:56:07 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

t_cmd	*createlist(int id, char *s, t_env *env, t_minishell *t_mini)
{
	char	**str;
	t_cmd	*new;

	new = (t_cmd *)ft_malloc(sizeof(t_cmd));
	str = splitline(s);
	new->allcmd = splitline(s);
	new->command = init_linkedlist_commandline(str, env, t_mini);
	new->redirection = init_linkedlist_redirection(str, env, t_mini);
	new->id_pipline = id;
	new->next = NULL;
	freememory(str);
	return (new);
}

t_cmd	*lastlist(t_cmd *l)
{
	if (!l)
		return (NULL);
	while (l->next != NULL)
		l = l->next;
	return (l);
}

void	addbacklist(t_cmd **pip, t_cmd *new)
{
	t_cmd	*lst;

	lst = lastlist(*pip);
	if (lst == NULL)
		*pip = new;
	else
		lst->next = new;
}

t_cmd	*createsruct(char **str, t_env *env, t_minishell *t_mini)
{
	int		i;
	t_cmd	*new;

	new = NULL;
	i = 0;
	while (str[i])
	{
		if (i > 0)
			t_mini->is_specific_case = true;
		addbacklist(&new, createlist(i, str[i], env, t_mini));
		i++;
	}
	if (!new)
		printerror("error\n");
	return (new);
}
