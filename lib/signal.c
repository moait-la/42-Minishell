/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 01:16:34 by mochenna          #+#    #+#             */
/*   Updated: 2024/09/20 21:56:21 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

void	handling_ctl_c(int sc)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)sc;
	get_exitst(1, true);
}

int	get_exitst(int status, bool get)
{
	static int	sts;

	if (get)
		sts = status;
	return (sts);
}

void	signal_herdoc(int sc)
{
	if (sc == SIGINT)
		close(0);
	get_exitst(-99, true);
}
