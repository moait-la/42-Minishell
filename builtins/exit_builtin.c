/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:52:27 by mochenna          #+#    #+#             */
/*   Updated: 2024/10/02 16:10:42 by mochenna         ###   ########.fr       */
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
	*is = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			s = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((r > LONG_MAX / 10) || (r == LONG_MAX / 10
				&& (str[i] - '0') > LONG_MAX % 10))
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
		if (!(s[i] >= '0' && s[i] <= '9') && s[i] != ' '
			&& !(s[i] >= '\t' && s[i] <= '\r'))
			return (true);
		i++;
	}
	return (false);
}

void	handling_status_exit(t_exit *e, t_minishell *m)
{
	if ((e->status % 2 == 0 || e->status == 0
			|| e->status == 1337) && e->status != 1)
	{
		m->is_exit = true;
		printf("exit\n");
		if (e->status == 0 && !e->in_pip)
			m->exit_value = get_exitst(0, true);
		else if ((e->status == 0 && e->in_pip) || e->status == 4)
			m->is_exit = false;
		if (e->status == 2 || e->is_overflow == 1)
		{
			printf("minishel: exit: numeric argument required \n");
			m->exit_value = get_exitst(255, true);
		}
		else if (e->status == 4)
		{
			printf("minishell: exit: too many arguments\n");
			m->exit_value = get_exitst(1, true);
		}
		else if (e->status == 1337)
			m->exit_value = get_exitst(e->n, true);
	}
	else
		exit_utils(e->status, e->is_overflow, e->n);
}

void	ft_exit(t_minishell *m, t_cmd *cmd)
{
	t_exit	exit;

	exit.status = 0;
	exit.in_pip = false;
	if (cmd->id_pipline > 0 || m->allpip != 0)
		exit.in_pip = true;
	if (!cmd->allcmd[1])
		exit_utils_(exit.in_pip, &exit.status, 0, 1);
	else if (ft_not_digit(cmd->command[1], cmd->allcmd[1]))
		exit_utils_(exit.in_pip, &exit.status, 2, 3);
	else if (cmd->command[2] != 0)
		exit_utils_(exit.in_pip, &exit.status, 4, 5);
	else if (!exit.in_pip)
		exit.status = 1337;
	else
		exit.status = -1337;
	if (exit.status == 1337 || exit.status == -1337)
		exit.n = ft_atol(cmd->command[1], &exit.is_overflow);
	handling_status_exit(&exit, m);
}
