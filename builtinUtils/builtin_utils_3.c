/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:11:34 by moait-la          #+#    #+#             */
/*   Updated: 2024/10/02 16:29:11 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

void	ft_update_env_lst(char *pwd, char *oldpwd, t_env *env_lst)
{
	if (!ft_getenv("OLDPWD", env_lst))
		ft_add_env(&env_lst, 0, "OLDPWD", "");
	if (!ft_getenv("PWD", env_lst))
		ft_add_env(&env_lst, 0, "PWD", pwd);
	while (env_lst)
	{
		if (!ft_strcmp(env_lst->key, "PWD"))
		{
			free(env_lst->value);
			env_lst->value = ft_strdup(pwd);
			if (!env_lst->value)
				return ;
		}
		else if (!ft_strcmp(env_lst->key, "OLDPWD"))
		{
			free(env_lst->value);
			env_lst->value = ft_strdup(oldpwd);
			if (!env_lst->value)
				return ;
		}
		env_lst = env_lst->next;
	}
}

char	*ft_goto_prev_dir(t_env *env_lst)
{
	char	*old_pwd;

	old_pwd = ft_getenv("OLDPWD", env_lst);
	if (!old_pwd)
	{
		ft_error("cd: ", "OLDPWD not set\n");
		get_exitst(1, true);
		return (NULL);
	}
	ft_putstr_fd(old_pwd, 1);
	ft_putstr_fd("\n", 1);
	return (ft_strdup(old_pwd));
}

int	ft_check_ifroot(char *path)
{
	while (*path)
	{
		if (*path != '/')
			return (1);
		path++;
	}
	return (0);
}

int	ft_plus_check(char *cmd)
{
	int	k;

	k = -1;
	while (cmd[++k] && cmd[k] != '=')
	{
		if (cmd[k] == '+' && cmd[k + 1] == '=')
			return (0);
	}
	return (1);
}
