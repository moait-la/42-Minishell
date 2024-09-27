/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 07:27:15 by moait-la          #+#    #+#             */
/*   Updated: 2024/09/24 00:16:47 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

int	ft_child_process(t_cmd *cmd, t_minishell *t_mini, int *fds, \
						t_created_pids **created_pids)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		get_exitst(1, true);
		ft_kill(*created_pids);
		return (free(t_mini->path), perror("fork"), -1);
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		ft_redirect_io_for_cmd(cmd);
		ft_close_pipe_fds(t_mini->allpip, fds);
		if (execve(t_mini->path, cmd->command, t_mini->envp) == -1)
			return (get_exitst(1, true), perror(strerror(errno)), -1);
	}
	ft_addto_created_pids(created_pids, pid);
	if (!cmd->next)
		t_mini->last_child_pid = pid;
	return (free(t_mini->path), 0);
}

static int	ft_handle_command(t_minishell *t_mini, t_env **env_lst, int *fds, \
								t_created_pids **created_pids)
{
	int		mybool;

	if (!t_mini->cmd->command)
		return (0);
	if (!ft_is_builtin(t_mini->cmd->command[0]))
		ft_execute_builtin(t_mini, t_mini->cmd, env_lst);
	else
	{
		t_mini->path = ft_get_path(t_mini->cmd->command[0], *env_lst, t_mini);
		if (!t_mini->path)
			return (0);
		mybool = ft_child_process(t_mini->cmd, t_mini, fds, created_pids);
		if (mybool == -1)
			return (-1);
	}
	return (0);
}

void	ft_execute_cmd(t_minishell *t_mini, t_env **env_lst, int *pipe_fds, \
						t_open_fds **open_fds)
{
	int				i;
	int				offset;
	t_cmd			*temp;
	t_created_pids	*created_pids;

	i = -1;
	offset = 0;
	temp = t_mini->cmd;
	created_pids = NULL;
	while (++i <= t_mini->allpip)
	{
		ft_init_pipe_fds_for_cmd(t_mini->cmd, pipe_fds, i);
		if (ft_redirect(t_mini, open_fds, &offset, 0) == -1)
			return ;
		if (ft_handle_command(t_mini, env_lst, pipe_fds, &created_pids) == -1)
			break ;
		t_mini->cmd = t_mini->cmd->next;
	}
	t_mini->cmd = temp;
	ft_close_open_fds(*open_fds);
	clean_created_pids(created_pids);
	ft_wait(t_mini, -1);
}

void	ft_execute(t_minishell	*t_mini, t_env **env_lst)
{
	t_open_fds	*open_fds;
	int			*pipe_fds;

	open_fds = NULL;
	pipe_fds = ft_open_pipes(t_mini, &open_fds);
	ft_init_start_data(t_mini);
	ft_open_heredoc(t_mini, *env_lst, &open_fds);
	if (!t_mini->cmd->command[0] && !t_mini->allpip \
			&& !t_mini->cmd->redirection[0])
	{
		ft_close_open_fds(open_fds);
		return (free(pipe_fds));
	}
	ft_update_udnerscore(t_mini->cmd->command, env_lst);
	ft_execute_cmd(t_mini, env_lst, pipe_fds, &open_fds);
	free(pipe_fds);
}
