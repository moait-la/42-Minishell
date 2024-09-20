/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:52:27 by mochenna          #+#    #+#             */
/*   Updated: 2024/09/19 00:35:13 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

long	ft_atol(char *str, int *is)
{
	long	r;
	int		s;
	int		i;

	i = 0;
	s = 1;
	r = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			s = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((r > LONG_MAX / 10)
			|| (r == LONG_MAX / 10 && (str[i] - '0') > LONG_MAX % 10))
			return ((*is = 1));
		r = r * 10 + (str[i] - '0');
		i++;
	}
	return (r * s);
}

bool	ft_not_digit(char *s, char *s1)
{
	int	i;

	i = 0;
	if (!check_if_quoted(s1) && !s[0])
		return (false);
	if (s[0] == 0 || countword(s, ' ') == 0)
		return (true);
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9')
			&& s[i] != ' ' && !(s[i] >= '\t' && s[i] <= '\r'))
			return (true);
		i++;
	}
	return (false);
}

bool	r_function(int n, int *st, bool ret, int value)
{
	if (n == 1)
		printerror("minishel: exit: : numeric argument required \n");
	else
		printerror("minishell: exit: too many arguments\n");
	*st = value;
	return (ret);
}

bool	ft_exit(t_minishell *m, t_env *e, char **s, int *st)
{
	char	*str;
	int		is_overflow;
	long	n;

	printerror("exit\n");
	if (!s[1])
	{
		*st = get_exitst(0, false);
		return (true);
	}
	str = expanding(s[1], e, m);
	if (ft_not_digit(str, s[1]))
		return (free(str), r_function(1, st, true, get_exitst(255, true)));
	else if (s[2] != 0)
		return (free(str), r_function(2, st, false, -1));
	is_overflow = 0;
	n = ft_atol(str, &is_overflow);
	if (is_overflow == 1)
		return (free(str),
			r_function(1, st, true, get_exitst(255, true)));
	*st = (int)(n & 255);
	return (true);
}
