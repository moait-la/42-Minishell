/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:48:56 by mochenna          #+#    #+#             */
/*   Updated: 2024/09/10 01:46:57 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

char	*ft_num_variable(char *s, int *p, int e)
{
	int		i;
	char	*str;
	int		j;

	i = *p;
	j = i;
	while (i < e)
	{
		if (s[i] == '$')
			break ;
		i++;
	}
	str = ft_strrange(s, j, i);
	*p = i;
	return (str);
}

int	ft_count_variable(char *s, int start, int end)
{
	int	c;

	c = 0;
	while (start < end)
	{
		if (s[start] == '$')
		{
			start++;
			while (s[start] && s[start] != '$' && ft_isalnum(s[start]))
				start++;
			start--;
			c++;
		}
		else
		{
			while (s[start] && s[start] != '$')
				start++;
			start--;
			c++;
		}
		start++;
	}
	return (c);
}

char	**ft_expanding_variable_split(char *s, t_expanding *e)
{
	char	**str;
	int		j;
	int		i;

	e->len = ft_count_variable(s, e->start, e->end);
	str = ft_malloc_double(e->len);
	i = e->start;
	j = 0;
	while (i < e->end)
	{
		if (s[i] == '$')
		{
			str[j] = get_key(s + i);
			i += ft_strlen(str[j++]) - 1;
		}
		else
		{
			str[j++] = ft_num_variable(s, &i, e->end);
			i--;
		}
		i++;
	}
	return (str);
}

char	*value_exit_status(char *key, bool is_spec)
{
	char	*str;
	int		status;

	if (is_spec)
		status = 0;
	else
		status = get_exitst(0, false);
	get_exitst(0, true);
	if (key[1] == 0)
		return (ft_itoa(status));
	str = ft_itoa(status);
	str = create_str(str, ft_strrange(key, 1, ft_strlen(key)), 1);
	return (str);
}

char	*create_str(char *r, char *s, int g)
{
	char	*str;

	if (g == 0)
	{
		str = ft_strdup(r);
		str = joinline(str, s);
	}
	else
		str = joinline(r, s);
	free(s);
	return (str);
}
