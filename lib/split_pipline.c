/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:08:43 by mochenna          #+#    #+#             */
/*   Updated: 2024/09/14 16:19:07 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

char	**splitpipline(char *s, int pip)
{
	int		i;
	char	**str;
	int		j;
	t_use	u;

	i = 0;
	j = 0;
	pip++;
	str = ft_malloc_double(pip);
	while (s[i])
	{
		if (s[i] != '|')
		{
			u.start = i;
			i = ft_skips(s, i);
			u.end = i--;
			str[j++] = ft_strrange(s, u.start, u.end);
		}
		i++;
	}
	return (str);
}

char	*ft_strrange(char *s, int start, int end)
{
	int		i;
	char	*str;

	str = ft_malloc(end - start + 1);
	i = 0;
	while (start < end)
		str[i++] = s[start++];
	return (str);
}
