/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 06:31:29 by moait-la          #+#    #+#             */
/*   Updated: 2024/09/19 19:23:12 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

int	check_if_quoted(char *eof)
{
	while (*eof)
	{
		if (*eof == '\'' || *eof == '\"')
			return (1);
		eof++;
	}
	return (0);
}

static void	heredoc(t_cmd *cmd, t_env *env_lst, t_minishell *t_mini,
		t_open_fds **open_fds)
{
	int		fds[2];
	char	*line;
	int		do_expand;

	do_expand = check_if_quoted(t_mini->eof);
	if (pipe(fds) == -1)
		return (perror("pipe"), exit(get_exitst(1, true)));
	cmd->in = fds[0];
	ft_add_to_open_fds(open_fds, cmd->in);
	t_mini->cpy_dup = dup(0);
	while (1)
	{
		signal(SIGINT, signal_herdoc);
		line = readline("> ");
		if (!line || !ft_strcmp(line, t_mini->eof))
			break ;
		if (!do_expand)
			line = expanding_heredoc(line, env_lst, t_mini);
		putstr_fd(fds[1], line, "\n");
		free_multi(line, NULL, NULL);
	}
	dup2_and_close(t_mini->cpy_dup, fds[1]);
	free_multi(line, NULL, NULL);
}

void	ft_open_heredoc(t_minishell *t_mini, t_env *env_lst, \
							t_open_fds **open_fds)
{
	int		j;
	int		i;
	t_cmd	*temp;

	temp = t_mini->cmd;
	while (t_mini->cmd)
	{
		i = -1;
		j = 0;
		while (t_mini->cmd->allcmd[++i])
		{
			if (!ft_strcmp(t_mini->cmd->allcmd[i], "<<"))
			{
				t_mini->eof = t_mini->cmd->redirection[j];
				heredoc(t_mini->cmd, env_lst, t_mini, open_fds);
				j++;
			}
		}
		t_mini->cmd = t_mini->cmd->next;
	}
	t_mini->cmd = temp;
}
