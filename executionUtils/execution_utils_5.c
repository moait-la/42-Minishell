/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 21:07:12 by moait-la          #+#    #+#             */
/*   Updated: 2024/10/02 17:30:25 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

void	ft_wait(t_minishell *t_mini, int i)
{
	int		status;
	pid_t	pid;

	while (++i < t_mini->allpip + 1)
	{
		pid = wait(&status);
		if (!t_mini->allpip || pid == t_mini->last_child_pid)
		{
			if (WIFEXITED(status))
				get_exitst(WEXITSTATUS(status), true);
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
				{
					write(2, "\n", 1);
					get_exitst(130, true);
				}
				else if (WTERMSIG(status) == SIGQUIT)
				{
					write(2, "Quit: 3\n", 9);
					get_exitst(131, true);
				}
			}
		}
	}
}

void	ft_init_pipe(t_cmd *cmd, t_open_fds **open_fds)
{
	int	fds[2];

	if (cmd->next != NULL)
	{
		if (pipe(fds) == -1)
			return (perror("pipe"), exit(1));
		cmd->out = fds[1];
		if (cmd->next->in == 0)
			cmd->next->in = fds[0];
		ft_add_to_open_fds(open_fds, fds[1]);
		ft_add_to_open_fds(open_fds, fds[0]);
	}
}

void	ft_redirect_io_for_cmd(t_cmd *cmd)
{
	if (cmd->in != 0)
	{
		if (dup2(cmd->in, STDIN_FILENO) == -1)
			return (perror("dup2"), exit(get_exitst(1, true)));
	}
	if (cmd->out != 1)
	{
		if (dup2(cmd->out, STDOUT_FILENO) == -1)
			return (perror("dup2"), exit(get_exitst(1, true)));
	}
}

void	ft_add_to_open_fds(t_open_fds **open_fds, int fd)
{
	t_open_fds	*new;
	t_open_fds	*tmp;

	new = (t_open_fds *)ft_malloc(sizeof(t_open_fds));
	new->fd = fd;
	new->next = NULL;
	if (!*open_fds)
		*open_fds = new;
	else
	{
		tmp = *open_fds;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	*ft_exec_file_check(char *cmd)
{
	char	*tmp;
	int		mybool;

	tmp = cmd;
	mybool = 1;
	while (*tmp)
	{
		if (*tmp == '/' || *tmp == '.')
			mybool = 0;
		tmp++;
	}
	if (access(cmd, F_OK) != 0 && !mybool)
		return (get_exitst(127, true), perror(strerror(errno)), NULL);
	if (access(cmd, X_OK) != 0 && !mybool)
		return (get_exitst(126, true), perror(strerror(errno)), NULL);
	return ("1337");
}
