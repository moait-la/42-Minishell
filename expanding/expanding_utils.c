/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:21:10 by mochenna          #+#    #+#             */
/*   Updated: 2024/08/31 16:37:28 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

int	ft_skip_value(char *line, int i, int f)
{
	char	quote;

	if (f == 1)
	{
		while (line[i])
		{
			if (line[i] == '\"' || line[i] == '\'')
				break ;
			i++;
		}
	}
	else if (f == 0)
	{
		quote = line[i++];
		while (line[i])
			if (line[i++] == quote)
				break ;
	}
	return (i);
}

int	ft_counts_expanding(char *s)
{
	int		i;
	int		c;

	i = 0;
	c = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			i = ft_skip_value(s, i, 0) - 1;
			c++;
		}
		else
		{
			i = ft_skip_value(s, i, 1) - 1;
			c++;
		}
		i++;
	}
	return (c);
}

char	**expanding_split(char *s)
{
	t_expanding	e;
	int			i;
	int			j;
	char		**str;

	e.len = ft_counts_expanding(s);
	str = ft_malloc_double(e.len);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			e.start = i;
			i = ft_skip_value(s, i, 0) - 1;
		}
		else
		{
			e.start = i;
			i = ft_skip_value(s, i, 1) - 1;
		}
		str[j++] = ft_strrange(s, e.start, i + 1);
		i++;
	}
	return (str);
}

char	*get_key(char *s)
{
	t_expanding	e;
	int			i;
	char		*str;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			e.start = i++;
			while (s[i] && !special_letter(s[i]))
				i++;
			e.end = i;
			break ;
		}
		i++;
	}
	str = ft_strrange(s, e.start, e.end);
	return (str);
}

bool	checkexpanding(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (true);
		i++;
	}
	return (false);
}
