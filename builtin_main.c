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

//this function returns 1 if a builtin matched
//0 if no builtin matched
//open issues:
//valgrind for cd, pwd, env, echo, unset okay
//restructure export

void	ft_transfer_ll_to_ptr(t_compound *cmds)
{
	int	i;
	t_env *current;
	
	i = 0;
	current = find_node(cmds, "PATH");
	
	//if PATH unset or value of PATH is empty
	if (!current || !current->value)
		return ;
	if (cmds->envp)
		free_double_ptr(cmds->envp);
	if (current->value)
	{
		cmds->envp = ft_split(current->value, ':');
		if (!cmds->envp)
			return ;
	}
}

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
	
	/***************THIS IS TO TRANSFER LL TO DOUBLE PTR**************/
	/*(the function is in this file, scoll up:)*/
	int i = 0;
	ft_transfer_ll_to_ptr(cmds);
	while (cmds->envp[i])
	{
		write (1, cmds->envp[i], ft_strlen(cmds->envp[i]));
		write (1, "\n", 1);
		i++;
	}
	/******************************************************************/
	
	
	/*****TO REMOVE REMAINING VALGRIND FREES; COMMENT THIS IN*********/
	// cleanup_envp_ll(cmds->env_ll);
	// free_double_ptr(cmds->envp);
	/******************************************************************/
	
	//if no builtin matched, 0 will be returned, proceed with pipex
	// else
	// 	return (0);
	//if a buitin matched, the return will be 1
	return (1);
}
