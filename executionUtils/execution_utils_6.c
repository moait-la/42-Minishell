/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_6.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 23:50:29 by moait-la          #+#    #+#             */
/*   Updated: 2024/09/19 01:41:22 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

void	ft_addto_created_pids(t_created_pids **created_pids, pid_t pid)
{
	t_created_pids	*new;
	t_created_pids	*tmp;

	new = (t_created_pids *)ft_malloc(sizeof(t_created_pids));
	new->pid = pid;
	new->next = NULL;
	if (!*created_pids)
		*created_pids = new;
	else
	{
		tmp = *created_pids;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	clean_created_pids(t_created_pids *created_pids)
{
	t_created_pids	*tmp;

	while (created_pids)
	{
		tmp = created_pids->next;
		free(created_pids);
		created_pids = tmp;
	}
}

void	ft_kill(t_created_pids *created_pids)
{
	while (created_pids)
	{
		kill(created_pids->pid, SIGKILL);
		created_pids = created_pids->next;
	}
}
