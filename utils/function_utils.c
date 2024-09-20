/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 22:28:53 by mochenna          #+#    #+#             */
/*   Updated: 2024/09/06 17:46:46 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
}

char	*makeline(char *s, t_minishell *mini)
{
	char	*str;
	int		i;
	int		j;

	str = ft_malloc((mini->allpip * 2)
			+ ft_strlen(s) + (mini->redirection * 2));
	i = -1;
	j = 0;
	while (s[++i])
	{
		if (s[i] == 39 || s[i] == 34)
			j = put_quots(str, s, &i, j);
		else if (s[i] == '>' || s[i] == '<' || s[i] == '|')
		{
			str[j++] = ' ';
			if (s[i] == '>' || s[i] == '<')
				j = correct_redirection(s, str, &i, j);
			else
				str[j++] = s[i];
			str[j++] = ' ';
		}
		else
			str[j++] = s[i];
	}
	return (str);
}

int	ft_get_position(char *s, int i, char l)
{
	while (s[i])
	{
		if (s[i] == l)
			return (i);
		i++;
	}
	return (0);
}
