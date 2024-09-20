/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:53:16 by mochenna          #+#    #+#             */
/*   Updated: 2024/09/19 00:39:16 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishel.h"

void	excuteprogram(t_minishell *minishell, t_env **env_lst)
{
	char	**str;

	global_counter(minishell, minishell->read);
	minishell->str = makeline(minishell->read, minishell);
	if (handling_status(checkglobal(minishell->str)))
		return ;
	str = splitpipline(minishell->str, minishell->allpip);
	minishell->cmd = createsruct(str, *env_lst, minishell);
	freememory(str);
	ft_execute(minishell, env_lst);
	clean(minishell, *env_lst);
}

void	minishell_program(t_minishell *minishell, t_env **env_lst)
{
	char	*prompt;

	while (42)
	{
		init_the_struct(minishell);
		prompt = ft_make_prompt(*env_lst);
		if (!prompt)
			return ;
		signal(SIGINT, handling_ctl_c);
		signal(SIGQUIT, SIG_IGN);
		minishell->read = readline(prompt);
		if (minishell->read == NULL)
		{
			printf("%s%s\n", prompt, "exit");
			free(prompt);
			exit(get_exitst(0, false));
		}
		add_history(minishell->read);
		if (countword(minishell->read, ' ') > 0
			&& if_out(minishell, *env_lst, prompt))
			excuteprogram(minishell, env_lst);
		free(minishell->read);
		free(prompt);
	}
}

int	main(int ac, char **av, char **env)
{
	t_minishell		minishell;
	t_env			*env_lst;

	if (!isatty(STDIN_FILENO))
	{
		printerror("OPS!: you can not redirect to minishell \n");
		exit(1);
	}
	(void)ac;
	(void)av;
	rl_catch_signals = 0;
	minishell.env_passed = 0;
	env_lst = ft_parse_envp(env, &minishell, 0);
	minishell_program(&minishell, &env_lst);
	rl_clear_history();
	return (get_exitst(0, false));
}
