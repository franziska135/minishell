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


int	main_old(int argc, char *argv[], char *envp[])
{
	if (argv[1])
	{
		t_execute		execute;
		t_compound	cmds;
		t_simple	scmd1;
		t_simple	scmd2;

		cmds.nbr_scmd = 1;
		cmds.scmd = malloc(sizeof(t_simple) * 2);
		if (!cmds.scmd)
			return (0);
		scmd1.cmd = malloc(sizeof(char *) * 10);
		if (!scmd1.cmd)
			return (free(cmds.scmd), 0);
		scmd2.cmd = malloc(sizeof(char *) * 10);
		if (!scmd2.cmd)
			return (free(scmd1.cmd), free(cmds.scmd), 0);
		scmd1.cmd[0] = malloc(100 + 1);
		if (!scmd1.cmd[0])
			return (free(scmd1.cmd), free(scmd2.cmd), free(cmds.scmd), 0);
		scmd1.cmd[1] = malloc(100 + 1);
		if (!scmd1.cmd[1])
			return (free(scmd1.cmd[0]), free(scmd1.cmd), free(scmd2.cmd), free(cmds.scmd), 0);
		scmd1.cmd[2] = malloc(100 + 1);
		if (!scmd1.cmd[2])
			return (0);
		scmd1.cmd[3] = malloc(100 + 1);
		if (!scmd1.cmd[3])
			return (0);
		scmd1.cmd[4] = malloc(100 + 1);
		if (!scmd1.cmd[4])
			return (0);
		scmd2.cmd[0] = malloc(100 + 1);
		if (!scmd2.cmd[0])
			return (0);
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
	/*this belongs to the beginng at booting shell:*/
	if (init_env_llist(&cmds, envp) == 0)
		return (0);
	/*mohammad has a working init function, run it*/

	//builtin_env(cmds.env_ll);
	init_path_struct(&execute);
	// //splits the path if one exists, otherwise does nothing, error message is later at access
	split_binary_paths(&execute, &cmds);
	process_commands(&execute, &cmds);
	//cleanup(&execute, &cmds);
	}
}
//determines what process shall be used, one parent/one child/pipex
void	process_commands(t_execute *execute, t_compound *cmds)
{
	if (cmds->nbr_scmd == 1)
	{
		//if its a builtin, the function will return 1 and no pipex will run
		if (if_builtin_execute(cmds, &cmds->scmd[0]) == 0)
			write(1, "no builtin\n", 11);
			//pipex
	}
	else
		write(1, "no single command\n", 11);
		//pipex
}

//this function returns 1 if a builtin matched
//0 if no builtin matched
int	if_builtin_execute(t_compound *cmds, t_simple *scmd)
{
	if (ft_strncmp(scmd->cmd[0], "echo\0", 6) == 0)
		builtin_echo(scmd);
	else if (ft_strncmp(scmd->cmd[0], "cd\0", 3) == 0)
		builtin_cd(scmd, cmds);
	else if (ft_strncmp(scmd->cmd[0], "pwd\0", 4) == 0)
		builtin_pwd();
	else if (ft_strncmp(scmd->cmd[0], "export\0", 7) == 0)
		builtin_export(cmds, scmd);
	else if (ft_strncmp(scmd->cmd[0], "unset\0", 6) == 0)
		builtin_unset(cmds, scmd);
	else if (ft_strncmp(scmd->cmd[0], "env\0", 4) == 0)
		builtin_env(cmds->env_ll);
	else if (ft_strncmp(scmd->cmd[0], "exit\0", 6) == 0)
		printf("exit\n");
	//if no builtin matched, 0 will be returned, proceed with pipex
	else
		return (0);
	//if a buitin matched, the return will be 1
	return (1);
}
