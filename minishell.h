/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2023/12/15 17:10:23 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define EXIT 1
# define CANT_OPEN 1
# define NOT_ENOUGH_ARGUMENTS 2
# define CMD_NOT_FOUND 3

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

//command table
typedef struct s_simple_command
{
	char	**command;
	char	*infile;
	char	**hd_delimiter;
	int		out_fd;

}	t_simple;

//global struct
typedef struct s_compound_command
{
	t_simple	**cmd;
	char	*cmd_line;

}	t_compound;


typedef struct s_path
{
	char	**paths_split;
	char	*path;
	int		index_path;
	char	**envp;
	int		path_amt;
}	t_path;

#endif