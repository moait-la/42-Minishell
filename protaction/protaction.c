/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protaction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 01:21:35 by mochenna          #+#    #+#             */
/*   Updated: 2024/09/09 17:43:55 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

char	*ft_malloc(size_t size)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(size + 1);
	if (!str)
	{
		ft_allocation_error();
		exit(get_exitst(1, true));
	}
	i = 0;
	while (i <= size)
		str[i++] = 0;
	return (str);
}

char	**ft_malloc_double(size_t size)
{
	char	**str;
	size_t	i;

	str = (char **)malloc((size + 1) * sizeof(char *));
	if (!str)
	{
		ft_allocation_error();
		exit(get_exitst(1, true));
	}
	i = 0;
	while (i <= size)
		str[i++] = 0;
	return (str);
}

char	*ft_strdup(char *s)
{
	char	*str;

	if (!s)
		return (NULL);
	str = ft_malloc(ft_strlen(s));
	ft_strcpy(str, s);
	return (str);
}

char	*joinline(char *s1, char *s2)
{
	char	*str;
	int		len;

	if (!s1)
		return (ft_strdup(s2));
	len = ft_strlen(s1);
	str = ft_malloc(len + ft_strlen(s2));
	ft_strcpy(str, s1);
	ft_strcpy(str + len, s2);
	free(s1);
	return (str);
}
