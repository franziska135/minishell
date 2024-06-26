/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2024/01/07 15:50:35 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define EXIT 1
# define CANT_OPEN 1
# define NOT_ENOUGH_ARGUMENTS 2
# define CMD_NOT_FOUND 3
# define TRUE 1
# define FALSE 0

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <libgen.h>
# include <signal.h>
# include <spawn.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"

extern int	g_signal;

//command table
typedef struct s_simple_command
{
	char	**cmd;
	char	**cmd_flag;
	int		in_fd;
	int		out_fd;
}	t_simple;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				env_display;
	struct s_env	*next;
}	t_env;

//global struct
typedef struct s_compound_command
{
	t_simple	*scmd;
	char		ms_path[200];
	size_t		nbr_scmd;
	char		**envp;
	t_env		*env_ll;
	int			exit_status;
	char		*pwd;
}	t_compound;

// HISTORY
int		run_minishell(t_compound	*cmds);

// SYNTAX
int		syntax(char *str, t_compound *cmds);

// LEXIS
char	**lexis(char *str);

// PARSER
char	**parser(t_compound *cmds, char **tokens);
char	*remove_quotes(char *str);
int		ft_here_doc(char *delimiter, t_compound *cmds, int expand);
char	*find_key(char *token);
size_t	tokens_counter(char **tokens);
int		struct_cpy(t_compound *cmds, char **tokens);
int		malloc_struct(t_compound *cmds, char **tokens);

// PARSER UTILS
int		is_delimiter(char c);
int		in_quot(char *str, size_t n);
size_t	token_counter(char *str);
char	**open_redir(t_compound *cmds, char **tokens);
void	close_fds(t_compound *cmds);
void	ambiguous(t_compound *cmds, char **tokens);
int		ft_word_count(char *str, char *flag);
char	*create_str(char *s, int *i, int len, char flag);

// 	REDIRECTIONS
void	redir_out(t_compound *cmds, char *file, int pipe, size_t *i);
void	redir_in(t_compound *cmds, char *file, int pipe, size_t *i);
void	redir_append(t_compound *cmds, char *file, int pipe, size_t *i);

//  EXPAND
// char	*token_expand(t_compound *cmds, char *token);
char	**expand_redir(t_compound *cmds, char *token);
char	**scmds_expand(t_compound *cmds, char **scmds);
int		expand_token(t_compound *cmds, char *token, int fd[2][2]);
int		write_expansion(t_compound *cmds, char *token, int fd[2][2], int flag);
char	**expansion_split(char *s, char *flag);

// PIPEX
int		piping_root(t_compound *cmds);
char	*path_finder(t_compound *cmds, int pipe);

// UTILS
void	struct_free(t_compound cmds);
void	dpointer_free(char **str);
void	struct_nullifier(t_compound *cmds);
int		is_built_in(char *str);
void	which_error(t_compound *cmds, char *path);
void	print_eof_hd(char *delim);
void	finish_hd(char *gnl, int fd[2]);
void	fork_fail(t_compound *cmds, int *fd, int initial_stdin);
int		parent_fail(t_compound *cmds, int fd[2], int in_std);
int		isit_path(char *str);
//t_env	*find_node(t_compound *cmds, char *needle);

// utils to be deleted
void	print_struct(t_compound ccmd);
void	print_dpointer(char **str);
void	err_handler(char *str);

//ENV && NODE
int		init_env_llist(t_compound *cmds, char **envp);
int		initiate_static_env_variables(t_compound *cmds);
int		initiate_static_env_variables2(t_compound *cmds);
int		sinitiate_static_env_variables3(t_compound *cmds);
void	free_node(void *node);
t_env	*find_node(t_compound *cmds, char *needle);
t_env	*ft_new_env_node(char *key, char *value, int env_display);
void	ft_add_last_node(t_env **lst, t_env *new);
int		ft_init_ll_loop(t_compound *cmds, char **envp, t_env *new_node, int i);
size_t	iterate_ultil_equal(const char *envp_i);

//BUILTIN
int		if_builtin_execute(t_compound *cmds, t_simple *scmd, int t, int fd[2]);
void	builtin_pwd(t_compound *cmds);
int		builtin_cd(t_simple *simple_command, t_compound *cmds);
int		update_env_ll(t_compound *cmds, char *variable, char *new_value);
void	builtin_env(t_env *head, t_simple *scmd, t_compound *cmds);
void	builtin_echo(t_compound *cmds, t_simple *s_cmd);
void	if_echo_home(t_compound *cmds);
int		check_for_n(t_simple *s_cmd);
int		check_for_only_n(char *str);
void	builtin_echo_write(t_compound *cmds, t_simple *s_cmd, int i);
int		builtin_unset(t_compound *cmds, t_simple *scmd);
int		builtin_unset_loop(t_compound *cmds, t_env *h, t_env *tmp, char *n);
int		builtin_export(t_compound *cmds, t_simple *scmd);
int		builtin_exit(t_compound *cmds, t_simple *scmd, int fdout, int fd[2]);
int		too_many_arg(t_simple *scmd);
int		is_digit(t_simple *scmd);
int		long_max(t_simple *scmd);

//UTILS CD
void	set_flag_pwd(t_compound *cmds);
int		go_back_home(t_simple *scmd);
int		cd_error_check(t_simple *scmd);
int		builtin_cd_home(t_compound *cmds);
int		builtin_cd_dotdot(t_compound *cmds);
int		builtin_cd_back(t_compound *cmds);
int		builtin_cd_path(t_compound *cmds, t_simple *scmd);
int		update_oldpwd(t_compound *cmds, char *storage);
int		update_pwd(t_compound *cmds, char *new_value);

//UTILS EXPORT
void	print_export(t_env *head);
t_env	*find_smallest(t_env *head);
t_env	*find_target(t_env *head, t_env *last_printed);
void	builtin_export_print(t_env *next_print);
int		save_key_and_value(char **key, char **value, char *current_cmd);
int		adapt_node(t_compound *cmds, char *current_cmd, char *key, char *value);
int		new_node(t_compound *cmds, char *current_cmd, char *key, char *value);
int		equal_sign_and_value(char *cmd1);
int		export_error_check(t_compound *cmds, char *new_var);
char	*save_key(char *cmd1);
char	*save_value(char *cmd1);
void	free_export(char *key, char *value);
void	check_pwd_display(t_env *node);

//TRANSFORM LL TO DPTR FOR EXECV
int		ft_transfer_ll_to_env_ptr(t_compound *cmds);
int		ft_count_nodes(t_compound *cmds);
char	*pro_ft_strjoin(char *s1, char *s2);
void	print_double_ptr(t_compound *cmds);

//CLEANING
void	cleanup_envp_ll(t_env *env_ll);
void	free_double_ptr(char **double_ptr);
void	free_env(t_simple **cmd);
void	ft_free_node(t_env *lst);
void	print_error(char *str2, char *str3, char *str4);
void	ft_free_single_node(t_env *node);
void	set_status(t_compound *cmds, int i);

//SIGNALS
void	non_interactive_mode(t_compound *cmds);
void	interactive_mode(t_compound *cmds);
void	backslash_non_interactive(int signum);
void	ctrlc_handler(int signum);
void	ctrlc_non_interactive(int signum);
void	ctrlc_hd(int sig);
void	signal_hd(t_compound *cmds);
void	backslash_hd(int sig);
void	signal_inhibition(t_compound *cmds);

#endif
