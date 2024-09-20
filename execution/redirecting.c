/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 08:50:58 by moait-la          #+#    #+#             */
/*   Updated: 2024/09/19 01:40:49 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

int	handle_appand(t_minishell *t_mini, t_open_fds **open_fds, \
					int *offset, int i)
{
	if (check_ambiguous(&t_mini->str[*offset + 3], t_mini->cmd->redirection[i]))
		return (-1);
	t_mini->cmd->out = open_file(t_mini->cmd->redirection[i], 3, t_mini);
	if (t_mini->cmd->out == -1)
		return (-1);
	ft_add_to_open_fds(open_fds, t_mini->cmd->out);
	(*offset)++;
	return (0);
}

int	handle_in(t_minishell *t_mini, t_open_fds **open_fds, int *offset, int i)
{
	if (check_ambiguous(&t_mini->str[*offset + 2], t_mini->cmd->redirection[i]))
		return (-1);
	t_mini->cmd->in = open_file(t_mini->cmd->redirection[i], 1, t_mini);
	if (t_mini->cmd->in == -1)
		return (-1);
	ft_add_to_open_fds(open_fds, t_mini->cmd->in);
	return (0);
}

int	handle_out(t_minishell *t_mini, t_open_fds **open_fds, int *offset, int i)
{
	if (check_ambiguous(&t_mini->str[*offset + 2], t_mini->cmd->redirection[i]))
		return (-1);
	t_mini->cmd->out = open_file(t_mini->cmd->redirection[i], 2, t_mini);
	if (t_mini->cmd->out == -1)
		return (-1);
	ft_add_to_open_fds(open_fds, t_mini->cmd->out);
	return (0);
}

int	ft_redirect(t_minishell *t_mini, t_open_fds **open_fds, int *offset, int i)
{
	while (t_mini->str[*offset] && t_mini->str[*offset] != '|')
	{
		if (t_mini->str[*offset] == '\"' || t_mini->str[*offset] == '\'')
			*offset = ft_skip_value(t_mini->str, *offset, 0) - 1;
		if (!ft_strncmp(&t_mini->str[*offset], ">>", 2))
		{
			if (handle_appand(t_mini, open_fds, offset, i++) == -1)
				return (-1);
		}
		else if (!ft_strncmp(&t_mini->str[*offset], "<<", 2))
		{
			(*offset)++;
			i++;
		}
		else if (t_mini->str[*offset] == '<')
		{
			if (handle_in(t_mini, open_fds, offset, i++))
				return (-1);
		}
		else if (t_mini->str[*offset] == '>')
			if (handle_out(t_mini, open_fds, offset, i++) == -1)
				return (-1);
		(*offset)++;
	}
	return ((*offset)++, 0);
}
