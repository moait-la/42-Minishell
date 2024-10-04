/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 03:20:18 by moait-la          #+#    #+#             */
/*   Updated: 2024/09/28 15:13:01 by mochenna         ###   ########.fr       */
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
		current_path = ft_strdup("minishell");
	home_path = ft_getenv("HOME", env_lst);
	path = ft_make_path(current_path, home_path);
	prompt = ft_generate_prompt(path);
	free_multi(current_path, path, NULL);
	return (prompt);
}

char	*joinchar(char *s, char c)
{
	char	*str;
	int		i;

	if (!s)
	{
		str = ft_malloc(1);
		str[0] = c;
		return (str);
	}
	str = ft_malloc(ft_strlen(s) + 1);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = c;
	free(s);
	return (str);
}
