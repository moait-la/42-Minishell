/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkglobal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 00:30:58 by mochenna          #+#    #+#             */
/*   Updated: 2024/09/20 19:36:08 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

bool	checkpip(char **str, int len)
{
	int	i;

	if (!ft_strcmp(str[0], "|") || !ft_strcmp(str[len - 1], "|"))
		return (true);
	i = -1;
	while (str[++i])
	{
		if (!ft_strcmp(str[i], "|"))
		{
			if (!ft_strcmp(str[i + 1], "&&") || !ft_strcmp(str[i + 1], "|")
				|| !ft_strcmp(str[i + 1], "&"))
				return (true);
			else if (!ft_strcmp(str[i - 1], ">>")
				|| !ft_strcmp(str[i - 1], "<<")
				|| !ft_strcmp(str[i - 1], "<") || !ft_strcmp(str[i - 1], ">"))
				return (true);
		}
	}
	return (false);
}

bool	checkredirection(char **str, int len)
{
	int	i;

	if ((!ft_strcmp(str[0], "<<") || !ft_strcmp(str[0], ">>")
			|| !ft_strcmp(str[0], "<") || !ft_strcmp(str[0], ">")) && len == 1)
		return (true);
	if (!ft_strcmp(str[len - 1], ">>") || !ft_strcmp(str[len - 1], "<<")
		|| !ft_strcmp(str[len - 1], "<") || !ft_strcmp(str[len - 1], ">"))
		return (true);
	i = 0;
	while (str[i])
	{
		if ((!ft_strcmp(str[i], "<<") || !ft_strcmp(str[i], ">>")
				|| !ft_strcmp(str[i], "<") || !ft_strcmp(str[i], ">")))
		{
			if (!ft_strcmp(str[i + 1], "<<") || !ft_strcmp(str[i + 1], ">>")
				|| !ft_strcmp(str[i + 1], "<") || !ft_strcmp(str[i + 1], ">"))
				return (true);
		}
		i++;
	}
	return (false);
}

bool	handling_status(int r)
{
	if (r == 0)
		return (false);
	else if (r == 1)
		printerror("minishell: syntax error \n");
	else if (r == 2)
		printerror
		("minishell: syntax error [in this minishel i\'m not handling ()]\n");
	else if (r == 3)
		printerror("minishell: \" not closed\n");
	else if (r == 4)
		printerror("minishell: \' not closed\n");
	return (true);
}

int	checkglobal(char *s)
{
	int		len;
	int		error_status;
	char	**str;

	error_status = 0;
	if (handiling_quots_parenthesis(s, &error_status))
		get_exitst(1, true);
	else
	{
		str = splitline(s);
		len = ft_strlen_double(str);
		if (checkpip(str, len) || checkredirection(str, len))
		{
			error_status = 1;
			get_exitst(258, true);
		}
		freememory(str);
	}
	if (error_status > 0)
		free(s);
	return (error_status);
}
