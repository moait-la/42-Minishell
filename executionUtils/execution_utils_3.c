/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:03:14 by moait-la          #+#    #+#             */
/*   Updated: 2024/09/19 19:27:12 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

void	ft_init_pipe_fds_for_cmd(t_cmd *cmd, int *pipe_fds, int i)
{
	if (cmd->next != NULL)
	{
		if (cmd->next->in == 0)
			cmd->next->in = pipe_fds[i * 2];
		cmd->out = pipe_fds[i * 2 + 1];
	}
}

void	ft_close_open_fds(t_open_fds *open_fds)
{
	t_open_fds	*temp;

	while (open_fds)
	{
		close(open_fds->fd);
		temp = open_fds;
		open_fds = open_fds->next;
		free(temp);
	}
}

int	*ft_open_pipes(t_minishell *t_mini, t_open_fds **open_fds)
{
	int	*fds;
	int	i;

	i = -1;
	fds = (int *)ft_malloc(sizeof(int) * t_mini->allpip * 2);
	while (++i < t_mini->allpip)
	{
		if (pipe(&fds[i * 2]) == -1)
			return (perror("pipe"), exit(1), NULL);
	}
	i = -1;
	while (++i < t_mini->allpip * 2)
		ft_add_to_open_fds(open_fds, fds[i]);
	return (fds);
}

void	putstr_fd(int fd, char *str1, char *str2)
{
	int	i;

	if (!str1 || fd < 0)
		return ;
	i = -1;
	while (str1[++i] != '\0')
		write(fd, &str1[i], 1);
	i = -1;
	while (str2[++i])
		write(fd, &str2[i], 1);
}

void	ft_close_pipe_fds(int pipe_count, int *fds)
{
	int	i;

	i = -1;
	while (++i < (pipe_count * 2))
		close(fds[i]);
}
