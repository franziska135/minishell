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

#include "minishell.h"
#include "execute.h"

int	main(int argc, char *argv[])
{
	if (argv[1])
	{
	t_list		execute;
	t_compound	compound;
	t_simple	simple1;
	t_simple	simple2;

		compound.amt_simple_cmds = 1;
		simple1.command = malloc(sizeof(char *));
		simple2.command = malloc(sizeof(char *));
		simple1.command[0] = malloc(100 + 1);
		simple1.command[1] = malloc(100 + 1);
		simple2.command[0] = malloc(100 + 1);
		strcpy(simple1.command[0], argv[1]);
		if (argv[2])
			strcpy(simple1.command[1], argv[2]);
		else 
			simple1.command[1] = NULL;
		strcpy(simple2.command[0], "cat");
		compound.cmd = malloc(sizeof(t_simple *));
		compound.cmd[0] = &simple1;
		compound.cmd[1] = &simple2;
	init_path_struct(&execute);
	//splits the path if one exists, otherwise does nothing, error message later
	split_binary_paths(&execute, &compound);
	// printf("check");
	tweak_simple_commands(&execute, &compound);
	process_commands(&execute, &compound);
	printf("children:%d\n", execute.amt_children);
	printf("pipes:%d\n", execute.amt_pipes);
	// builtins(&m, argc, argv;
//	cleanup(&execute, &compound);
	}
}
//determines what process shall be used, one parent/one child/pipex
void	process_commands(t_list *execute, t_compound *compound)
{
	if (execute->amt_children == 0)
		execute_builtin(compound->cmd[0]);
	// else if (execute->amt_children == 1)
	// 	//execute_one_child()
	// else
	// 	//execute_pipex()
}

void	tweak_simple_commands(t_list *execute, t_compound *compound)
{
	flag_builtins(compound->cmd);
	//is it correct to assume that there is at least one command?
	if (compound->amt_simple_cmds > 1 || compound->cmd[0]->builtin == FALSE)
	{
		execute->amt_children = compound->amt_simple_cmds;
		execute->amt_pipes = compound->amt_simple_cmds - 1;
		int i = 0;
		printf("\n");
		while (i < compound->amt_simple_cmds)
		{
		printf("command %d: \t%s\n", i, compound->cmd[i]->command[0]);
		printf("builtin: \t%d\n", compound->cmd[i]->builtin);
		i++;
		}
	}
	else
		printf("only one command: %s\n", compound->cmd[0]->command[0]);
		//else: the default value of amt children and amt pipes is set to 0
}

void	execute_builtin(t_simple *simple_command)
{
	if (simple_command->builtin == ECHO)
		printf("echo\n");
		//builtin_echo();
	else if (simple_command->builtin == CD)
		// printf("cd\n");
		builtin_cd(simple_command);
	else if (simple_command->builtin == PWD)
		builtin_pwd();
	else if (simple_command->builtin == EXPORT)
		printf("export\n");
		//builtin_export();
	else if (simple_command->builtin == UNSET)
		printf("unset\n");
		//builtin_unset();
	else if (simple_command->builtin == ENV)
		printf("env\n");
		//builtin_env();
	else if (simple_command->builtin == B_EXIT)
		printf("exit\n");
		//builtin_exit();
}


void	flag_builtins(t_simple **cmd)
{
	int	i;

	i = 0;
	//assuming that there is at least one simple command struct!
	//strncmp -> with how many digits?
	while (cmd[i])
	{
		if(ft_strncmp(cmd[i]->command[0], "echo", 5) == 0)
			cmd[i]->builtin = ECHO;
		else if (ft_strncmp(cmd[i]->command[0], "cd", 2) == 0)
			cmd[i]->builtin = CD;
		else if (ft_strncmp(cmd[i]->command[0], "pwd", 3) == 0)
			cmd[i]->builtin = PWD;
		else if (ft_strncmp(cmd[i]->command[0], "export", 6) == 0)
			cmd[i]->builtin = EXPORT;
		else if (ft_strncmp(cmd[i]->command[0], "unset", 5) == 0)
			cmd[i]->builtin = UNSET;
		else if (ft_strncmp(cmd[i]->command[0], "env", 3) == 0)
			cmd[i]->builtin = ENV;
		else if (ft_strncmp(cmd[i]->command[0], "exit", 4) == 0)
			cmd[i]->builtin = B_EXIT;
		else
			cmd[i]->builtin = FALSE;
		i++;
	}
}
