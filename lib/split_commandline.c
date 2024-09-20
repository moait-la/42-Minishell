/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commandline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 01:22:18 by mochenna          #+#    #+#             */
/*   Updated: 2024/09/20 18:55:09 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

int	ft_skip(char *line, int i)
{
	char	quot;

	while (line[i])
	{
		if (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
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

int	ft_counts_word(char *s)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (s[i])
	{
		if (s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13))
		{
			i = ft_skip(s, i) - 1;
			c++;
		}
		i++;
	}
	return (c);
}

char	**splitline(char *s)
{
	char	**str;
	int		i;
	int		j;
	t_use	u;

	i = 0;
	j = 0;
	u.len = ft_counts_word(s);
	str = ft_malloc_double(u.len);
	while (s[i])
	{
		if (s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13))
		{
			u.start = i;
			i = ft_skip(s, i);
			u.end = i--;
			str[j++] = ft_strrange(s, u.start, u.end);
		}
		i++;
	}
	return (str);
}
