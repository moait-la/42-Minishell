/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 21:17:52 by mochenna          #+#    #+#             */
/*   Updated: 2024/09/11 17:14:42 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

bool	check_if_split(char *s, char *exp)
{
	int	i;

	i = 0;
	if (exp[0] == 0)
		return (false);
	while (s[i])
	{
		if (s[i] == '=')
			return (false);
		i++;
	}
	if ((countword(exp, ' ') > 1
			&& (ft_count(s, '\"') > 0 || ft_count(s, '\'') > 0)))
		return (false);
	return (true);
}

void	fetch_expanding_variable(t_list **head,
	char *s, char *expand, int index)
{
	char	**str;
	int		i;

	i = 0;
	if (do_nothing(expand, s))
	{
		free(expand);
		return ;
	}
	else if (check_if_split(s, expand) && checkexpanding(s))
	{
		str = ft_split(expand, ' ');
		while (str[i])
			ft_lstadd_back(head, ft_lstnew(ft_strdup(str[i++])));
		freememory(str);
	}
	else
	{
		if (expand[0] == 0 && index == 0)
			ft_lstadd_back(head, ft_lstnew(ft_strdup("#")));
		else
			ft_lstadd_back(head, ft_lstnew(ft_strdup(expand)));
	}
	free(expand);
}

t_list	*create_linkedlist(char **s, t_env *env, t_minishell *t_mini)
{
	t_list	*head;
	int		i;

	i = 0;
	head = NULL;
	while (s[i])
	{
		if (!ft_strcmp(s[i], ">>") || !ft_strcmp(s[i], "<<")
			|| !ft_strcmp(s[i], "<") || !ft_strcmp(s[i], ">"))
			i++;
		else
			fetch_expanding_variable(&head, s[i],
				expanding(s[i], env, t_mini), i);
		i++;
	}
	return (head);
}

char	**init_linkedlist_commandline(char **s, t_env *env, t_minishell *t_mini)
{
	char	**str;
	int		i;
	t_list	*head;
	t_list	*clear;

	head = create_linkedlist(s, env, t_mini);
	str = ft_malloc_double(ft_lstsize(head));
	clear = head;
	i = 0;
	while (head != NULL)
	{
		clear = head->next;
		str[i++] = ft_strdup(head->str);
		free(head->str);
		free(head);
		head = clear;
	}
	return (str);
}

char	**init_linkedlist_redirection(char **s, t_env *env, t_minishell *t_mini)
{
	int		i;
	int		len;
	int		j;
	char	**str;

	i = 0;
	j = 0;
	len = count_redirection(s);
	if (len == 0)
		return (NULL);
	str = ft_malloc_double(len);
	while (s[i])
	{
		if (!ft_strcmp(s[i], ">>") || !ft_strcmp(s[i], "<<")
			|| !ft_strcmp(s[i], "<") || !ft_strcmp(s[i], ">"))
		{
			if (!ft_strcmp(s[i], "<<"))
				str[j++] = ft_strdup(s[i + 1]);
			else
				str[j++] = expanding(s[i + 1], env, t_mini);
		}
		i++;
	}
	return (str);
}
