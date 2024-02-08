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
# include "./libft/libft.h"

# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"

//command table
typedef struct s_simple_command
{
	char	**cmd;
	int		in_fd;
	int		out_fd;
	int		builtin; //a 0/1 flag for execution
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
}	t_compound;

typedef struct s_execute
{
	char	**binary_paths;
}	t_execute;

// HISTORY
int		run_minishell(t_compound	*cmds);

// SYNTAX
int		syntax(char *str);

// LEXIS
char	**lexis(char *str);

// PARSER
char	**parser(t_compound *cmds, char **tokens);
char	*remove_quotes(char *str);
int		ft_here_doc(char *delimiter);
int		struct_cpy(t_compound *cmds, char **tokens);

// PARSER UTILS
int		is_delimiter(char c);
int		in_quot(char *str, size_t n);
size_t	token_counter(char *str);
char	**open_redir(t_compound *cmds, char **tokens);
void	close_fds(t_compound *cmds, int *fd);
void	ambiguous(t_compound *cmds, char **tokens);
char	**expansion_split(char *s);

//  EXPAND
// char	*token_expand(t_compound *cmds, char *token);
char	*expand_redir(t_compound *cmds, char *token);
char	**scmds_expand(t_compound *cmds, char **scmds);
void	expand_token(t_compound *cmds, char *token, int *fd);

// PIPEX
int		piping_root(t_compound *cmds);
char	*path_finder(t_compound *cmds, int pipe);

// UTILS
void	struct_free(t_compound cmds);
void	dpointer_free(char **str);
void	struct_nullifier(t_compound *cmds);
int		init_env_llist(t_compound *cmds, char **envp);
int		ft_transfer_ll_to_env_ptr(t_compound *cmds);
t_env	*find_node(t_compound *cmds, char *needle);

// utils to be deleted
void	print_struct(t_compound ccmd);
void	print_dpointer(char **str);
void	err_handler(char *str);

//node stuff
void	free_node(void *node);
t_env	*find_node(t_compound *cmds, char *needle);
t_env	*ft_new_env_node(char *key, char *value, int env_display);
void	ft_add_last_node(t_env **lst, t_env *new);

//check amt of commands and pipes, children
void	process_commands(t_execute *execute, t_compound *compound);
int		if_builtin_execute(t_compound *compound, t_simple *simple_command);

//builtins
void	builtin_pwd(void);
int		builtin_cd(t_simple *simple_command, t_compound *cmds);
int		builtin_cd_home(t_compound *cmds);
int		builtin_cd_dotdot(t_compound *cmds);
int		builtin_cd_back(t_compound *cmds);
int		builtin_cd_path(t_compound *cmds, t_simple *scmd);
int		update_env_ll(t_compound *cmds, char *variable, char *new_value);
void	builtin_env(t_env *head);
void	builtin_echo(t_simple *s_cmd);
int		check_for_n(t_simple *s_cmd);
int		check_for_only_n(char *str);
void	builtin_echo_write(t_simple *s_cmd, int i);
void	builtin_unset(t_compound *cmds, t_simple *scmd);
int		builtin_export(t_compound *cmds, t_simple *scmd);
void	builtin_exit(t_compound *cmds);

//export utils
void	print_export(t_env *head);
int		save_key_and_value(char **key, char **value, t_simple *scmd);
int		adapt_node(t_compound *cmds, t_simple *scmd, char *key, char *value);
int		new_node(t_compound *cmds, t_simple *scmd, char *key, char *value);
int		equal_sign_and_value(char *cmd1);
int		export_error_check(t_compound *cmds, t_simple *scmd);
char	*save_key(char *cmd1);
char	*save_value(char *cmd1);
void	free_export(char *key, char *value);

//transformation from ll to double ptr for the environment var
int		ft_transfer_ll_to_env_ptr(t_compound *cmds);
int		ft_count_nodes(t_compound *cmds);
char	*pro_ft_strjoin(char *s1, char *s2);
void	print_double_ptr(t_compound *cmds);

//cleaning up at error
void	cleanup(t_execute *execute, t_compound *compound);
void	cleanup_envp_ll(t_env *env_ll);
void	free_double_ptr(char **double_ptr);
void	free_env(t_simple **cmd);
void	ft_free_node(t_env *lst);
void	print_error(char *str2, char *str3, char *str4);

#endif
