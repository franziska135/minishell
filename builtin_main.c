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

int	main(void)
{
	t_list		execute;
	t_compound	compound;
	t_simple	simple1;
	t_simple	simple2;

		compound.amt_simple_cmds = 2;
		simple1.command = malloc(sizeof(char *));
		simple2.command = malloc(sizeof(char *));
		simple1.command[0] = malloc(100 + 1);
		simple2.command[0] = malloc(100 + 1);
		strcpy(simple1.command[0], "echo");
		strcpy(simple2.command[0], "cat");
		compound.cmd = malloc(sizeof(t_simple *));
		compound.cmd[0] = &simple1;
		compound.cmd[1] = &simple2;
	init_path_struct(&execute);
	//splits the path if one exists, otherwise does nothing, error message later
	split_binary_paths(&execute, &compound);
	process_commands(&execute, &compound);
	printf("children:%d\n", execute.amt_children);
	printf("pipes:%d\n", execute.amt_pipes);
	// // builtins(&m, argc, argv;
	// cleanup(&execute, &compound);
}

void	process_commands(t_list *execute, t_compound *compound)
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

void	flag_builtins(t_simple **cmd)
{
	int	i;

	i = 0;
	//assuming that there is at least one simple command struct!
	//strncmp -> with how many digits?
	while (cmd[i])
	{
		if(ft_strncmp(cmd[i]->command[0], "echo", 5) == 0)
			cmd[i]->builtin = TRUE;
		else if (ft_strncmp(cmd[i]->command[0], "cd", 2) == 0)
			cmd[i]->builtin = TRUE;
		else if (ft_strncmp(cmd[i]->command[0], "pwd", 3) == 0)
			cmd[i]->builtin = TRUE;
		else if (ft_strncmp(cmd[i]->command[0], "export", 6) == 0)
			cmd[i]->builtin = TRUE;
		else if (ft_strncmp(cmd[i]->command[0], "unset", 5) == 0)
			cmd[i]->builtin = TRUE;
		else if (ft_strncmp(cmd[i]->command[0], "env", 3) == 0)
			cmd[i]->builtin = TRUE;
		else if (ft_strncmp(cmd[i]->command[0], "exit", 4) == 0)
			cmd[i]->builtin = TRUE;
		else
			cmd[i]->builtin = FALSE;
		i++;
	}
	
}