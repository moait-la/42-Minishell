/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:25:23 by mochenna          #+#    #+#             */
/*   Updated: 2024/09/20 19:36:28 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
# define MINISHEL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <termcap.h>
# include <termios.h>
# include "../libft/libft.h"
# define BOLD		"\033[1m"
# define COLOR_END	"\033[0m"
# define COLOR_START	"\033[38;5;46m"
# define WHITE		"\033[38;5;255m"
# define GREEN		"\033[38;5;154m"
# define COLOR_PATH	"\033[38;5;51m"
# define NOT_FOUND "minishell: command not found\n"
# define DEFAULT_PATH "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."

typedef struct s_env
{
	char			*key;
	char			*value;
	int				has_printed;
	int				mybool;
	struct s_env	*next;
}	t_env;

typedef struct s_open_fds
{
	int					fd;
	struct s_open_fds	*next;
}	t_open_fds;

typedef struct s_created_pids
{
	pid_t					pid;
	struct s_created_pids	*next;
}	t_created_pids;

typedef struct s_cmdline
{
	int					in;
	int					out;
	int					id_pipline;
	int					infile_not_valid;
	char				**allcmd;
	char				**command;
	char				**redirection;
	struct s_cmdline	*next;
}	t_cmd;

typedef struct s_use
{
	int		len;
	int		start;
	int		end;
	char	*str;
}	t_use;

typedef struct s_expan
{
	int		len;
	int		start;
	int		end;
	char	**str;
	char	*key;
	char	*value;
	bool	is_expand;
}	t_expanding;

typedef struct s_minishell
{
	char	*read;
	char	*str;
	char	*path;
	char	**arr;
	char	**redirections;
	char	**heredoc;
	char	**envp;
	char	*eof;
	int		allpip;
	int		redirection;
	int		exit_error;
	int		exit_st;
	int		env_passed;
	int		first_child_pid;
	int		last_child_pid;
	bool	is_specific_case;
	int		cpy_dup;
	t_cmd	*cmd;
}	t_minishell;

int		ft_count(char *s, char l);
int		ft_strlen_double(char **s);
int		ft_strcmp(char *s1, char *s2);
int		countword(char *s, char l);
char	*fex(char *s);
char	**splitpipline(char *s, int pip);
void	printerror(char *s);
char	*ft_strdup(char *s);
char	*ft_malloc(size_t size);
char	*joinline(char *s1, char *s2);
char	**ft_malloc_double(size_t size);
void	ft_strcpy(char *s1, char *s2);
void	dup2_and_close(int cpy_dup, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**splitline(char *s);
char	*ft_strrange(char *s, int start, int end);
char	*update_value_to_new_value(char *value, char *key, t_env *env_lst);
char	*ft_get_env_value(char *key, t_env *env_lst);
int		count_redirection(char **s);
void	init_the_struct(t_minishell *minishell);
void	*ft_exec_file_check(char *cmd);
void	ft_handle_env_update(char *key, char *value, char *cmd, t_env *env_lst);
bool	check_exit(char *s);
void	handling_ctl_c(int sc);
void	ft_sorted_envlst(t_cmd *cmd, t_env *env_lst, t_env	*smallest);
int		ft_counts_pip(char *s);
int		ft_skips(char *line, int i);
t_cmd	*createlist(int id, char *s, t_env *env, t_minishell *t_mini);
void	addbacklist(t_cmd **pip, t_cmd *new);
void	ft_update_export_lst(t_env *env_lst, char *key, char *value);
t_cmd	*createsruct(char **str, t_env *env, t_minishell *t_mini);
char	**get_option(char **str, int start, int end, int len);
char	**init_linkedlist_commandline(char **s,
			t_env *env, t_minishell *t_mini);
char	**init_linkedlist_redirection(char **s,
			t_env *env, t_minishell *t_mini);
bool	handling_status(int r);
int		checkglobal(char *s);
bool	checkexpanding(char *s);
char	**expanding_split(char *s);
int		ft_skip_value(char *line, int i, int f);
char	*get_key(char *s);
char	*expanding(char *s, t_env *env, t_minishell *t_mini);
int		ft_get_position(char *s, int i, char l);
char	*expanding_value(char *key, bool is_expand,
			t_env *env, t_minishell *t_mini);
char	*create_str(char *r, char *s, int g);
void	putstr_fd(int fd, char *str1, char *str2);
char	*value_exit_status(char *key, bool is_spec);
char	*expanding_heredoc(char *s, t_env *env, t_minishell *t_mini);
bool	special_letter(char l);
char	**ft_expanding_variable_split(char *s, t_expanding *e);
int		correct_redirection(char *s, char *str, int *i, int j);
char	*makeline(char *s, t_minishell *mini);
void	global_counter(t_minishell *minishell, char *s);
void	ft_addto_created_pids(t_created_pids **created_pids, pid_t pid);
int		status_check_first(t_minishell *mini, int c);
int		skip_quot(char *s, int i);
int		ft_openfile_error(void);
int		*ft_open_pipes(t_minishell *t_mini, t_open_fds **open_fds);
int		put_quots(char *str, char *s, int *p, int j);
int		ft_counts_word(char *s);
void	countpip(t_minishell *minishell, char *str);
bool	handiling_quots_parenthesis(char *s, int *status);
void	freememory(char **s);
void	ft_init_pipe_fds_for_cmd(t_cmd *cmd, int *pipe_fds, int i);
void	ft_redirect_io_for_cmd(t_cmd *cmd);
void	clean_created_pids(t_created_pids *created_pids);
void	ft_cd_perror(char *str);
void	clean(t_minishell *clean, t_env *env_lst);
void	out(char *s, char *s1);
char	*ft_get_value(char *cmd);
char	*ft_goto_prev_dir(t_env *env_lst);
void	ft_close_pipe_fds(int pipe_count, int *fds);
char	*ft_get_key(char *cmd);
t_env	*ft_create_node(char *env);
void	ft_execute(t_minishell	*t_mini, t_env **env_lst);
char	*ft_get_path(char *cmd, t_env *env_lst, t_minishell *t_mini);
char	*ft_getenv(char *key, t_env *env_lst);
void	ft_init_start_data(t_minishell *t_mini);
void	ft_kill(t_created_pids *created_pids);
void	ft_close_open_fds(t_open_fds *open_fds);
int		ft_plus_check(char *cmd);
void	ft_init_pipe(t_cmd *cmd, t_open_fds **open_fds);
void	ft_update_env_lst(char *pwd, char *oldpwd, t_env *env_lst);
void	ft_error(char *s1, char *s2);
int		open_file(char *name, int mybool, t_minishell *t_mni);
void	ft_free(char **ptr);
void	ft_add_to_open_fds(t_open_fds **open_fds, int fd);
void	ft_wait(t_minishell *t_mini, int i);
void	ft_reinit_has_printed(t_env *env_lst);
void	ft_allocation_error(void);
bool	if_out(t_minishell *m, t_env *e, char *prt);
void	ft_echo(t_cmd *cmd);
void	ft_print_export(t_cmd *cmd, t_env *smallest);
void	ft_cd(t_cmd *cmd, t_env *env_lst);
void	ft_env(t_cmd *cmd, t_env *env);
void	ft_pwd(t_cmd *cmd);
void	ft_export(t_cmd *cmd, t_env *env_lst);
void	ft_unset(t_cmd *cmd, t_env **env_lst);
int		is_valid_identifier(char *command);
int		ft_equal_sign(char *cmd);
int		ft_check_ifexists(char *key, t_env *env_lst);
int		ft_is_builtin(char *cmd);
void	ft_add_env(t_env **env_lst, int mybool, char *key, char *value);
void	ft_execute_builtin(t_minishell *t_mini, t_cmd *cmd, t_env **env_lst);
char	*ft_handle_point(t_cmd *cmd);
void	ft_clear_screen(void);
int		ft_arguments_nbr(char **command);
int		ft_check_ifroot(char *path);
int		ft_redirect(t_minishell *t_mini,
			t_open_fds **open_fds, int *offset, int i);
int		get_exitst(int status, bool get);
void	ft_open_heredoc(t_minishell *t_mini,
			t_env *env_lst, t_open_fds **open_fds);
t_env	*ft_parse_envp(char **envp, t_minishell *t_mini, int i);
void	free_multi(void *adrs1, void *adrs2, void *adrs3);
void	ft_update_udnerscore(char **command, t_env **env_lst);
char	*ft_make_prompt(t_env *env_lst);
int		ft_skip_env(char *envp, int i);
void	handling_ctl_child(int sc);
void	handling_sigquit(int sc);
void	handling_sigquit_child(int sc);
bool	do_nothing(char *expand, char *s);
bool	check_ambiguous(char *s, char *expand);
void	signal_herdoc(int sc);
int		check_if_quoted(char *eof);
bool	ft_exit(t_minishell *m, t_env *e, char **s, int *st);

#endif