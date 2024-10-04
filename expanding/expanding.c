/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:56:40 by mochenna          #+#    #+#             */
/*   Updated: 2024/09/27 22:31:52 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

char	*expanding_value(char *key, bool is_expand,
		t_env *env, t_minishell *t_mini)
{
	char	*value;

	value = NULL;
	if (is_expand && ft_strlen(key) > 1)
	{
		key++;
		if (key[0] >= '0' && key[0] <= '9')
			return (ft_strdup(key + 1));
		else if (t_mini->is_specific_case && key[0] == '_')
			return (ft_strdup(""));
		else if (!ft_strcmp(key, "PATH") && t_mini->env_passed == 1)
			return (ft_strdup(DEFAULT_PATH));
		else if (key[0] == '?')
			return (value_exit_status(key, t_mini->is_specific_case));
		while (env)
		{
			if (!ft_strcmp(key, env->key))
				return (ft_strdup(env->value));
			env = env->next;
		}
		value = ft_strdup("");
	}
	else
		value = ft_strdup(key);
	return (value);
}

char	*expanding_variable(char *s, t_expanding *e,
		t_env *env, t_minishell *t_mini)
{
	char	**str;
	char	*s1;
	int		i;

	str = ft_expanding_variable_split(s, e);
	i = 0;
	s1 = NULL;
	while (str[i])
	{
		if (checkexpanding(str[i]))
			s1 = create_str(s1,
					expanding_value(str[i], e->is_expand, env, t_mini), 1);
		else
			s1 = joinline(s1, str[i]);
		i++;
	}
	freememory(str);
	return (s1);
}

char	*expanding_type_one(char *r, char *s, t_env *env, t_minishell *t_mini)
{
	t_expanding	e;
	char		*str;

	e.end = ft_strlen(s);
	e.start = 0;
	e.is_expand = true;
	if (s[0] == '\'' || s[0] == '\"')
	{
		if (s[0] == '\'')
			e.is_expand = false;
		e.end--;
		e.start++;
	}
	str = expanding_variable(s, &e, env, t_mini);
	str = create_str(r, str, 1);
	return (str);
}

char	*expanding_type_tow(char *r, char *s)
{
	t_use	u;
	char	*ss;
	char	*str;

	u.len = ft_strlen(s);
	if (u.len == 2)
		return (joinline(r, ""));
	ss = ft_strrange(s, 1, u.len - 1);
	str = joinline(r, ss);
	free(ss);
	return (str);
}

char	*expanding(char *s, t_env *env, t_minishell *t_mini)
{
	int		i;
	char	**str;
	char	*result;

	str = expanding_split(s);
	result = NULL;
	i = 0;
	while (str[i])
	{
		if (checkexpanding(str[i]) && t_mini != NULL && env != NULL)
			result = expanding_type_one(result, str[i], env, t_mini);
		else
		{
			if (ft_count(str[i], '\"') > 0 || ft_count(str[i], '\'') > 0)
				result = expanding_type_tow(result, str[i]);
			else
				result = joinline(result, str[i]);
		}
		i++;
	}
	freememory(str);
	return (result);
}
