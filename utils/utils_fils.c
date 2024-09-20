/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:57:41 by mochenna          #+#    #+#             */
/*   Updated: 2024/09/07 16:01:43 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

bool	check_exit(char *s)
{
	char	**str;
	bool	exit;

	str = ft_split(s, ' ');
	exit = false;
	if (!ft_strcmp(str[0], "exit"))
		exit = true;
	freememory(str);
	return (exit);
}

bool	special_letter(char l)
{
	char	*s;
	int		i;

	i = 0;
	s = "$=/*-+\"\'@!#%^.*:";
	if (l == ' ' || (l >= 9 && l <= 13))
		return (true);
	while (s[i])
	{
		if (s[i] == l)
			return (true);
		i++;
	}
	return (false);
}
