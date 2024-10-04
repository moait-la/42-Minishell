/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:57:41 by mochenna          #+#    #+#             */
/*   Updated: 2024/10/02 16:08:46 by mochenna         ###   ########.fr       */
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

bool	if_not_containe_exit(t_minishell *m, t_env *e)
{
	char	*expand;
	bool	status;

	expand = expanding(m->cmd->allcmd[0], e, m);
	status = true;
	if (!ft_strncmp("exit", expand, 4)
		&& countword(expand, ' ') == 1)
	{
		if (expand[5])
			status = false;
	}
	else
		status = false;
	free(expand);
	return (status);
}

void	exit_utils(int status, int is_overflow, long n)
{
	if (status == 1)
		return ;
	get_exitst(255, true);
	if (status == 3)
		printf("minishel: exit: numeric argument required \n");
	else if (status == 5)
	{
		get_exitst(1, true);
		printf("minishell: exit: too many arguments\n");
	}
	else if (status == -1337)
	{
		if (is_overflow == 1)
			printf("minishel: exit: numeric argument required \n");
		else
			get_exitst(n, true);
	}
}

void	exit_utils_(bool is_pip, int *status, int v1, int v2)
{
	if (!is_pip)
		*status = v1;
	else
		*status = v2;
}
