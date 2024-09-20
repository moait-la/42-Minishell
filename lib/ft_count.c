/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:12:31 by mochenna          #+#    #+#             */
/*   Updated: 2024/09/12 15:27:10 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

int	count_redirection(char **s)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (s[i])
	{
		if (!ft_strcmp(s[i], ">>") || !ft_strcmp(s[i], "<<")
			|| !ft_strcmp(s[i], "<") || !ft_strcmp(s[i], ">"))
			c++;
		i++;
	}
	return (c);
}

int	ft_strlen_double(char **s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	global_counter(t_minishell *minishell, char *s)
{
	int		i;

	i = 0;
	minishell->allpip = ft_counts_pip(s);
	while (s[i])
	{
		if (s[i] == 39 || s[i] == 34)
			i = ft_skip_value(s, i, 0) - 1;
		else if (s[i] == '<' || s[i] == '>')
		{
			if ((s[i] == '<' && s[i + 1] == '<')
				|| (s[i] == '>' && s[i + 1] == '>'))
				i++;
			minishell->redirection++;
		}
		i++;
	}
}

int	ft_counts_pip(char *s)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
			i = ft_skip_value(s, i, 0) - 1;
		if (s[i] == '|')
			c++;
		i++;
	}
	return (c);
}

int	ft_count(char *s, char l)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == l)
			c++;
		i++;
	}
	return (c);
}
