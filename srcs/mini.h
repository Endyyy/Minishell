/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:14:43 by achretie          #+#    #+#             */
/*   Updated: 2023/02/22 16:01:09 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H
# include "../libs/libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <errno.h>

extern int				g_ret_val;
typedef enum e_type		t_type;
typedef struct s_token	t_token;

typedef enum e_type
{
	T_UNDEFINED,
	T_WORD,
	T_PIPE,
	T_REDIRECT,
	T_SPACE,
	T_ERROR
}				t_type;

typedef struct s_pex
{
	char	**envp;
	int		nb_cmd;
	char	*cmd;
	int		**fd;
	char	**full_cmd;
	int		*pid;
	pid_t	solo_pid;
	int		i;
}				t_pex;

struct s_token
{
	t_token	*next;
	t_token	*prev;
	char	*data;
	t_type	type;
};

typedef struct s_env
{
	char			*content;
	char			*key;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

typedef struct s_data
{
	t_env	*envp;
	int		bug;
	char	*input;
	int		ret_value;
	int		exit;
	char	*cmd;
	char	**full_cmd;
	int		pid;
	int		in;
	int		out;
	int		heredoc;
	int		builtin;
	int		pipe;
	int		pre_builtin;
}				t_data;

//ft_redir.c
int		ft_redir_db_great(char *pos, t_data *data);
int		ft_redir_great(char *pos, t_data *data);
int		ft_redir_db_less(char *pos, t_data *data, t_token *head, t_pex *p);
int		ft_redir_less(char *pos, t_data *data);

//ft_redir_parse.c
void	ft_redir_parse(t_data *data, t_token *args, t_token *head, t_pex *p);

//ft_pipe.c
void	ft_max_sleep(void);
void	ft_end_pipes(t_pex *p);
int		ft_exec_pipe(t_pex *p, t_data *data, t_token *args, t_token *tmp);
int		ft_case_last(t_pex *p, t_data *data, t_token *args, t_token *tmp);
int		ft_case_mid(t_pex *p, t_data *data, t_token *args, t_token *tmp);
int		ft_case_first(t_pex *p, t_data *data, t_token *args, t_token *tmp);

//ft_isbuiltin.c
int		ft_isbuiltin(t_token *args, t_data *data, char **clean_cmd, t_pex *p);
int		ft_isbuiltin_pipe(t_token *args, t_data *data, \
char **clean_cmd, t_pex *p);
int		ft_get_nb_cmd(t_token *args, t_pex *p);
int		ft_exec_cmd_builtin(t_data *data, char **args, char *clean_cmd);

//ft_manage_env.c
char	**ft_env_to_tab(t_data *data);
char	*ft_getenv(t_data *data, char *var);
int		ft_setenv(t_data *data, char *var, char *content);
void	ft_env_print(t_data *data, t_env *save);
void	ft_env_pipe(t_data *data, t_env *save);

//ft_utils.c
int		ft_get_length_start(t_token *start);
char	**ft_clean_to_tab_loop(t_token *start, char **tabl, int i);
char	**ft_clean_to_tab(t_token *start);
void	ft_wait_pipe(int status, t_pex *p, t_data *data);
void	ft_init_data(t_data *data, char **envp);

//ft_main_loop.c
void	ft_main_loop(t_pex *p, t_data *data, t_token *args);
void	ft_reset(t_data *data, t_pex *p);
int		ft_start_commands(t_data *data, t_token *args);
int		ft_free_path(char **data);
t_env	*ft_lstadd_front_env(char *content, t_env *head, int i);
char	*ft_get_key(char *content);
void	ft_add_to_env(t_data *data, char *arg);
void	ft_add_to_env_plus(t_data *data, char *arg);
char	*ft_execve_path(char **cmd, char **envp);

//builtins
int		ft_cd(t_data *data, char **tabl);
int		ft_exit(t_token *args, t_data *data, t_pex *p);
void	ft_pwd(t_data *data);
void	ft_export(t_data *data, char *var, t_pex *p);

//ft_parse
int		ft_free_path(char **data);
int		ft_start_exec(t_data *data, char **envp, char *input);
char	*ft_parse_input(char *input);
int		ft_try_access(char *cmd, char **envp);
char	*ft_parse_input_mini(char *input);
char	**ft_parse_path(char **envp);
void	ft_trap(int signal);

//utils_parse.c
int		ft_get_length(char **tabl);
int		ft_strcmp(char *s1, char *s2);

//parsing.c
t_token	*parser(char *str, t_env *env);
void	free_token(t_token *token);
t_env	*create_env(char **envp);
char	*get_value(t_env *env, char *key, bool nullValue);
void	env_var(t_token *token, t_env *env);
void	merge_token(t_token *token);
void	delete_space(t_token *token);
void	tmp_show(t_token *token);
char	*get_value(t_env *env, char *key, bool nullValue);
t_token	*create_token(t_token *token);
int		complete(t_token *token, char *str);
int		complete2(t_token *token, char *str, t_type type);
int		complete3(t_token *token, char *str);

// free.c
void	free_envp(t_env **envp);
void	free_tabint(int	**tabl, int size);
void	ft_check_status(int status);

//ft_exec.c
void	ft_redir_exec(t_pex *p, char **envp, t_data *data, t_token *args);
void	ft_exec_error(char *file);
void	ft_exec_cmd(t_pex *p, char **envp, t_data *data, t_token *args);

//ft_get_utils.c
int		ft_get_length(char **tabl);
int		ft_get_nb_cmd(t_token *args, t_pex *p);

//ft_print.c
void	ft_print_export(t_data *data);
char	*ft_remove_plus(char *arg);
size_t	get_index(char *src);

//ft_echo.c
void	ft_echo(char **args, t_data *data);
void	ft_echo_pipe(char **args, t_data *data);
void	ft_tryhard(int signal);

//ft_heredoc.c
void	ft_free_all(t_token *args, t_data *data, t_pex *p);
int		ft_check_is_num(char *s);
int		ft_heredoc(char *delim, t_token *head, t_data *data, t_pex *p);
int		ft_heredoc_loop(char *delim);
void	ft_unset(t_data *data, char *var);

//ft_init_env.c
t_env	*ft_lstnew_env(char *content);
t_env	*ft_lstnew_env_key(char *content);
t_env	*ft_lstnew_env_content(char *content);
void	ft_free_env_loop(t_data *data, char **envp, int i, char	*tmp_envp);

//ft_pipe_bis.c
void	ft_get_case_bis(t_pex *p);
void	ft_case_first_bis(t_pex *p, t_data *data, t_token *args, t_token *tmp);
void	ft_case_mid_bis(t_pex *p, t_data *data, t_token *args, t_token *tmp);
void	ft_case_last_bis(t_pex *p, t_data *data, t_token *args, t_token *tmp);

//ft_pipe_alpha.c
int		ft_case_last(t_pex *p, t_data *data, t_token *args, t_token *tmp);

//ft_main_loop_bis.c
void	ft_multi_cmd(t_pex *p, t_data *data, t_token *args, t_token *start);
int		ft_main_loop_bis(t_pex *p, t_token *start);

//ft_heredoc_bis.c
char	*ft_heredoc_loop_bis(char *stock, char *input);
void	ft_x(int signal);
int		ft_check_ret_val(char *stock, int tmp_fd);

//ft_echo_bis.c
int		ft_check_echo_flag(char **args, int i, t_data *data);

//ft_main_loop_3.c
int		ft_check_pipe_bis(t_token *start, t_token *tmp);
void	ft_free_all_heredoc(t_token *args, t_data *data, t_pex *p);
int		ft_check_if_builtin(char *arg);

//ft_manage_one_cmd.c
int		ft_one_cmd_bis(t_pex *p);
int		ft_one_cmd_loop(t_data *data, t_token *args, t_pex *p, int status);
int		ft_one_cmd(t_data *data, t_token *args, t_pex *p, int status);
void	ft_init_data(t_data *data, char **envp);
void	ft_env(t_data *data);

#endif