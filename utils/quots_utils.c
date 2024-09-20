/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quots_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:36:02 by mochenna          #+#    #+#             */
/*   Updated: 2024/09/06 01:24:43 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

int	skip_quot(char *s, int i)
{
	char	letter;

	letter = s[i];
	while (s[i])
	{
		if (s[i] == letter)
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

int	put_quots(char *str, char *s, int *p, int j)
{
	char	letter;
	int		i;

	i = *p;
	letter = s[i];
	str[j++] = s[i++];
	while (s[i])
	{
		if (s[i] == letter)
		{
			str[j++] = letter;
			break ;
		}
		str[j++] = s[i++];
	}
	*p = i;
	return (j);
}

bool	checkquots(char *s, int *i)
{
	char	q;

	q = s[(*i)++];
	while (s[*i])
	{
		if (s[*i] == q)
			return (false);
		(*i)++;
	}
	return (true);
}

bool	handiling_quots_parenthesis(char *s, int *status)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			if (s[i] == '\'')
			{
				if (checkquots(s, &i))
					*status = 4;
			}
			else
				if (checkquots(s, &i))
					*status = 3;
		}
		else if (s[i] == '(' || s[i] == ')')
			*status = 2;
		if (*status != 0)
			return (true);
		i++;
	}
	return (false);
}
