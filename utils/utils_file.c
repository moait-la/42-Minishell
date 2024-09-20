/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 22:27:14 by mochenna          #+#    #+#             */
/*   Updated: 2024/09/10 01:47:05 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

void	init_the_struct(t_minishell *minishell)
{
	minishell->read = NULL;
	minishell->str = NULL;
	minishell->allpip = 0;
	minishell->redirection = 0;
	minishell->exit_error = 0;
	minishell->is_specific_case = false;
	minishell->redirections = NULL;
	minishell->cmd = NULL;
}

int	correct_redirection(char *s, char *str, int *i, int j)
{
	char	red;

	red = s[*i];
	if (s[*i + 1] == red)
	{
		(*i)++;
		str[j++] = red;
		str[j++] = red;
	}
	else
		str[j++] = red;
	return (j);
}

bool	do_nothing(char *expand, char *s)
{
	return (expand[0] == 0 && !check_if_quoted(s));
}

char	*expanding_heredoc(char *s, t_env *env, t_minishell *t_mini)
{
	int		i;
	char	*str;
	char	*s1;
	t_use	u;

	str = NULL;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '\"' || s[i] == '\'')
			str = joinline(str, &s[i]);
		else
		{
			u.start = i;
			while (s[i] && s[i] != '\"' && s[i] != '\'')
				i++;
			u.str = ft_strrange(s, u.start, (u.end = i--));
			s1 = expanding(u.str, env, t_mini);
			free(u.str);
			str = create_str(str, s1, 1);
		}
	}
	free(s);
	return (str);
}

bool	check_ambiguous(char *s, char *expand)
{
	if (do_nothing(expand, s))
	{
		get_exitst(1, true);
		printerror("minishell: ambiguous redirect\n");
		return (true);
	}
	else if (ft_count(s, '\"') == 0 && ft_count(s, '\'') == 0)
	{
		if (countword(expand, ' ') > 1
			|| (expand[0] == '*' && expand[1] == 0))
		{
			get_exitst(1, true);
			printerror("minishell: ambiguous redirect\n");
			return (true);
		}
	}
	return (false);
}
