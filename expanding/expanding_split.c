/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 01:03:17 by mochenna          #+#    #+#             */
/*   Updated: 2024/08/31 16:41:44 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

char	*get_expand_word(char *s, int *p)
{
	t_use	u;
	int		i;
	char	*str;

	u.start = *p;
	i = *p;
	if (s[i] == '$')
	{
		i++;
		while (s[i] && s[i] != '$')
			i++;
	}
	else
	{
		while (s[i] && s[i] != '$')
			i++;
	}
	str = ft_strrange(s, u.start, i);
	*p = i;
	return (str);
}

char	**expand_split(char *s)
{
	int		i;
	char	**str;
	int		len;
	int		p;

	len = ft_count(s, '$');
	str = ft_malloc_double(len);
	i = 0;
	p = 0;
	while (i < len)
		str[i++] = get_expand_word(s, &p);
	return (str);
}
