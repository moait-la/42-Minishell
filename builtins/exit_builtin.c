/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:52:27 by mochenna          #+#    #+#             */
/*   Updated: 2024/09/24 21:23:49 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

long	ft_atol(char *str, int *is)
{
	long	r;
	int		s;
	int		i;

	i = 0;
	s = 1;
	r = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			s = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((r > LONG_MAX / 10)
			|| (r == LONG_MAX / 10 && (str[i] - '0') > LONG_MAX % 10))
			return ((*is = 1));
		r = r * 10 + (str[i] - '0');
		i++;
	}
	return (r * s);
}

bool	ft_not_digit(char *s, char *s1)
{
	int	i;

	i = 0;
	if (!check_if_quoted(s1) && !s[0])
		return (false);
	if (s[0] == 0 || countword(s, ' ') == 0)
		return (true);
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9')
			&& s[i] != ' ' && !(s[i] >= '\t' && s[i] <= '\r'))
			return (true);
		i++;
	}
	return (false);
}

void	put_value(t_minishell *m, int flag, int value, bool f_exit)
{
	if (flag == 1)
		printerror("minishel: exit: : numeric argument required \n");
	else
		printerror("minishell: exit: too many arguments\n");
	if (!f_exit)
		m->is_exit = false;
	m->exit_value = value;
}

bool	handling_exit(t_minishell *m, long n, int is_overflow)
{
	if (is_overflow == 1)
	{
		printerror("minishel: exit: : numeric argument required \n");
		m->exit_value = get_exitst(255, true);
		return (true);
	}
	m->exit_value = (int)(n & 255);
	return (false);
}

void	ft_exit(t_minishell *m, t_cmd *cmd)
{
	long	n;

	if (m->allpip != 0)
		return ;
	printerror("exit\n");
	m->is_exit = true;
	if (!cmd->allcmd[1])
	{
		m->exit_value = get_exitst(0, false);
		return ;
	}
	if (ft_not_digit(cmd->command[1], cmd->allcmd[1]))
	{
		put_value(m, 1, get_exitst(255, true), true);
		return ;
	}
	else if (cmd->command[2] != 0)
	{
		put_value(m, 2, get_exitst(1, true), false);
		return ;
	}
	m->is_overflow = 0;
	n = ft_atol(cmd->command[1], &m->is_overflow);
	if (handling_exit(m, n, m->is_overflow))
		return ;
}
