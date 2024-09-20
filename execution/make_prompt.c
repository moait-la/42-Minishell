/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 03:20:18 by moait-la          #+#    #+#             */
/*   Updated: 2024/09/10 23:39:02 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

static char	*ft_generate_prompt(char *path)
{
	int		len;
	char	*prompt;

	len = ft_strlen(BOLD) * 2 + ft_strlen(COLOR_START) + ft_strlen("minishell:")
		+ ft_strlen(COLOR_END) * 3 + ft_strlen(COLOR_PATH) + ft_strlen(path)
		+ ft_strlen(WHITE) * 2 + ft_strlen(" » ") + ft_strlen(":");
	prompt = (char *)ft_malloc(len);
	ft_strcpy(prompt, BOLD);
	ft_strcat(prompt, COLOR_START);
	ft_strcat(prompt, "minishell");
	ft_strcat(prompt, WHITE);
	ft_strcat(prompt, ":");
	ft_strcat(prompt, COLOR_END);
	ft_strcat(prompt, BOLD);
	ft_strcat(prompt, COLOR_PATH);
	ft_strcat(prompt, path);
	ft_strcat(prompt, COLOR_END);
	ft_strcat(prompt, GREEN);
	ft_strcat(prompt, " » ");
	ft_strcat(prompt, COLOR_END);
	return (prompt);
}

static char	*ft_make_path(char *current_path, char *home_path)
{
	int		len;
	char	*path;
	char	*check;
	char	*new_path;

	check = NULL;
	if (home_path != NULL)
		check = ft_strnstr(current_path, home_path, ft_strlen(current_path));
	if (check)
	{
		len = ft_strlen(current_path) - ft_strlen(home_path);
		new_path = ft_substr(current_path, ft_strlen(home_path), len);
		path = ft_strjoin("~", new_path);
		free(new_path);
	}
	else
		path = ft_strdup(current_path);
	return (path);
}

char	*ft_make_prompt(t_env *env_lst)
{
	char	*current_path;
	char	*home_path;
	char	*prompt;
	char	*path;

	current_path = getcwd(NULL, 0);
	if (!current_path)
	{
		putstr_fd(2, strerror(errno), "\n");
		return (get_exitst(18, true), NULL);
	}
	home_path = ft_getenv("HOME", env_lst);
	path = ft_make_path(current_path, home_path);
	prompt = ft_generate_prompt(path);
	free_multi(current_path, path, NULL);
	return (prompt);
}
