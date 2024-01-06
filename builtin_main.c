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

int	main(int argc, char *argv[], char *envp[])
{
	if (argv[1])
	{
	t_list		execute;
	t_compound	cmds;
	t_simple	scmd1;
	t_simple	scmd2;

		cmds.nbr_scmd = 1;
		cmds.scmd = malloc(sizeof(t_simple) * 2);
		scmd1.cmd = malloc(sizeof(char *) * 10);
		scmd2.cmd = malloc(sizeof(char *) * 10);
		scmd1.cmd[0] = malloc(100 + 1);
		scmd1.cmd[1] = malloc(100 + 1);
		scmd1.cmd[2] = malloc(100 + 1);
		scmd1.cmd[3] = malloc(100 + 1);
		scmd1.cmd[4] = malloc(100 + 1);
		scmd2.cmd[0] = malloc(100 + 1);
		strcpy(scmd1.cmd[0], argv[1]);
		
		if (argv[2])
			strcpy(scmd1.cmd[1], argv[2]);
		else 
			scmd1.cmd[1] = NULL;
		if (argv[3])
			strcpy(scmd1.cmd[2], argv[3]);
		else 
			scmd1.cmd[2] = NULL;
		if (argv[4])
			strcpy(scmd1.cmd[3], argv[4]);
		else 
			scmd1.cmd[3] = NULL;
		if (argv[5])
			strcpy(scmd1.cmd[4], argv[5]);
		else 
			scmd1.cmd[4] = NULL;
		strcpy(scmd2.cmd[0], "cat");
		cmds.scmd[0] = scmd1;
		cmds.scmd[1] = scmd2;
	cmds.envp = envp;
	init_path_struct(&execute);
	//splits the path if one exists, otherwise does nothing, error message later
	split_binary_paths(&execute, &cmds);
	//print_paths(&execute);
	// printf("check");
	tweak_simple_commands(&execute, &cmds);
	process_commands(&execute, &cmds);
	// printf("children:%d\n", execute.amt_children);
	// printf("pipes:%d\n", execute.amt_pipes);
	// builtins(&m, argc, argv;
	// cleanup(&execute, &cmds);
	}
}
//determines what process shall be used, one parent/one child/pipex
void	process_commands(t_list *execute, t_compound *cmds)
{
	if (execute->amt_children == 0)
	//write (1, "check", 5);
		execute_builtin(cmds, &cmds->scmd[0]);
	// else if (execute->amt_children == 1)
	// 	//execute_one_child()
	// else
	// 	//execute_pipex()
}

void	tweak_simple_commands(t_list *execute, t_compound *cmds)
{
	flag_builtins(cmds);
	//is it correct to assume that there is at least one command?
	if (cmds->nbr_scmd > 1 || cmds->scmd[0].builtin == FALSE)
	{
		execute->amt_children = cmds->nbr_scmd;
		execute->amt_pipes = cmds->nbr_scmd - 1;
		// int i = 0;
		// printf("\n");
		// while (i < compound->amt_simple_cmds)
		// {
		// printf("command %d: \t%s\n", i, compound->cmd[i]->command[0]);
		// printf("builtin: \t%d\n", compound->cmd[i]->builtin);
		// i++;
		// }
	}
	//else
	//printf("only one command: %s\n", compound->cmd[0]->command[0]);
	//else: the default value of amt children and amt pipes is set to 0
}

void	execute_builtin(t_compound *compound, t_simple *scmd)
{
	if (scmd->builtin == ECHO)
		builtin_echo(scmd);
	else if (scmd->builtin == CD)
		builtin_cd(scmd);
	else if (scmd->builtin == PWD)
		builtin_pwd();
	else if (scmd->builtin == EXPORT)
		printf("export\n");
		//builtin_export();
	else if (scmd->builtin == UNSET)
		printf("unset\n");
		//builtin_unset();
	else if (scmd->builtin == ENV)
		builtin_envp(compound);
	else if (scmd->builtin == B_EXIT)
		printf("exit\n");
		//builtin_exit();
}


void	flag_builtins(t_compound *cmds)
{
	int	i;

	i = 0;
	//assuming that there is at least one simple command struct!
	//strncmp -> with how many digits?
	//change to i < nbr_scmd
	while (i < cmds->nbr_scmd)
	{
		if(ft_strncmp(cmds->scmd[i].cmd[0], "echo", 5) == 0)
			cmds->scmd[i].builtin = ECHO;
		else if (ft_strncmp(cmds->scmd[i].cmd[0], "cd", 2) == 0)
			cmds->scmd[i].builtin = CD;
		else if (ft_strncmp(cmds->scmd[i].cmd[0], "pwd", 3) == 0)
			cmds->scmd[i].builtin = PWD;
		else if (ft_strncmp(cmds->scmd[i].cmd[0], "export", 6) == 0)
			cmds->scmd[i].builtin = EXPORT;
		else if (ft_strncmp(cmds->scmd[i].cmd[0], "unset", 5) == 0)
			cmds->scmd[i].builtin = UNSET;
		else if (ft_strncmp(cmds->scmd[i].cmd[0], "env", 3) == 0)
			cmds->scmd[i].builtin = ENV;
		else if (ft_strncmp(cmds->scmd[i].cmd[0], "exit", 4) == 0)
			cmds->scmd[i].builtin = B_EXIT;
		else
			cmds->scmd[i].builtin = FALSE;
		i++;
	}
}
