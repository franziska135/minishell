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

//command table
typedef struct s_simple_command
{
	char	**command;
	char	**hd_delimiter;
	int		in_fd;
	int		out_fd;
	int		builtin; //a 0/1 flag for execution
}	t_simple;

//global struct
typedef struct s_compound_command
{
	t_simple	**cmd;
	char		ms_path[200];
	int			amt_simple_cmds;
	char		**envp;
}	t_compound;
#endif