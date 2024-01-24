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


// HISTORY
int	run_minishell(t_compound	*cmds);

// SYNTAX
int	syntax(char *str);

// int	syntax_redir(char *str);

// LEXIS
char	**lexis(char *str);


// PARSER
char	**parser(t_compound *cmds, char **tokens);
char	*remove_quotes(char *str);
int	ft_here_doc(char *delimiter);
int	struct_cpy(t_compound *cmds, char **tokens);


// PARSER UTILS
int	is_delimiter(char c);
int	in_quot(char *str, size_t n);
size_t	token_counter(char *str);
char	**open_redir(t_compound *cmds, char **tokens);
void	close_fds(t_compound *cmds, int *fd);


//  EXPAND
char	**token_expand(t_compound *cmds, char **token);


// PIPEX
int	piping_root(t_compound *cmds);
char	*path_finder(t_compound *cmds, int pipe);



// UTILS
void	struct_free(t_compound cmds);
void	dpointer_free(char **str);
void	struct_nullifier(t_compound *cmds);
void	init_env_llist(t_compound *cmds, char **envp);
t_env	*find_node(t_compound *cmds, char *needle);




// utils to be deleted
void	print_struct(t_compound ccmd);
void	print_dpointer(char **str);
void	err_handler(char *str);



#endif
