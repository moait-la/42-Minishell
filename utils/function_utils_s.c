/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils_s.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:16:32 by mochenna          #+#    #+#             */
/*   Updated: 2024/08/31 16:46:41 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

int	countword(char *s, char l)
{
	int	v[3];

	if (!s)
		return (0);
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
	while (s[v[1]])
	{
		if (s[v[1]] == l)
			v[2] = 0;
		else if (!v[2])
		{
			v[2] = 1;
			v[0]++;
		}
		v[1]++;
	}
	return (v[0]);
}

void	printerror(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		write(2, &s[i++], 1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_skips(char *line, int i)
{
	char	quot;

	while (line[i])
	{
		if (line[i] == '|')
			break ;
		else if (line[i] == '\'' || line[i] == '\"')
		{
			quot = line[i++];
			while (line[i])
				if (line[i++] == quot)
					break ;
			i--;
		}
		i++;
	}
	return (i);
}
