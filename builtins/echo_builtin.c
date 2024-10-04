/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:19:43 by moait-la          #+#    #+#             */
/*   Updated: 2024/10/02 15:17:20 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

static int	ft_check_nl_flag(char **command, int *new_line)
{
	int	i;
	int	j;

	i = 1;
	while (command[i])
	{
		j = 0;
		if (command[i][0] == '-')
		{
			if (!command[i][1])
				return (i);
			while (command[i][++j])
			{
				if (command[i][j] != 'n')
					return (i);
			}
			(*new_line) = 1;
			i++;
		}
		else
			break ;
	}
	return (i);
}

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 0;
	if (!cmd->command[i])
	{
		ft_putchar_fd('\n', cmd->out);
		return ;
	}
	i = ft_check_nl_flag(cmd->command, &new_line);
	while (cmd->command[i])
	{
		ft_putstr_fd(cmd->command[i], cmd->out);
		if (cmd->command[i + 1])
			ft_putchar_fd(' ', cmd->out);
		i++;
	}
	if (new_line == 0)
		ft_putchar_fd('\n', cmd->out);
}
