/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 03:49:19 by moait-la          #+#    #+#             */
/*   Updated: 2024/09/20 19:07:34 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

int	ft_openfile_error(void)
{
	get_exitst(1, true);
	putstr_fd(2, strerror(errno), "\n");
	return (-1);
}

void	ft_error(char *s1, char *s2)
{
	ft_putstr_fd("minishell: ", 2);
	if (s1)
		ft_putstr_fd(s1, 2);
	if (s2)
		ft_putstr_fd(s2, 2);
	get_exitst(1, true);
}

void	ft_allocation_error(void)
{
	ft_putstr_fd("Allocation Failed!\n", 2);
	return ;
}

void	ft_free(char **ptr)
{
	char	**temp;

	if (!ptr)
		return ;
	temp = ptr;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(temp);
}

void	ft_cd_perror(char *str)
{
	get_exitst(1, true);
	perror(str);
}
