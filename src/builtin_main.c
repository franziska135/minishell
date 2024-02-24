/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2024/02/20 16:26:40 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this function returns 1 if a builtin matched
//0 if no builtin matched
//open issues:
//valgrind for cd, pwd, env, echo, unset okay
//restructure export
//if PATH is currently unset, value of PATH is empty
//and function returns nothing
//export & cd malloc protected
int	if_builtin_execute(t_compound *cmds, t_simple *scmd)
{
	if (ft_strncmp(scmd->cmd[0], "echo\0", 6) == 0)
		builtin_echo(cmds, scmd);
	else if (ft_strncmp(scmd->cmd[0], "cd\0", 3) == 0)
	{
		if (builtin_cd(scmd, cmds) == FALSE)
			return (0);
	}
	else if (ft_strncmp(scmd->cmd[0], "pwd\0", 4) == 0)
		builtin_pwd(cmds);
	else if (ft_strncmp(scmd->cmd[0], "export\0", 7) == 0)
	{
		if (builtin_export(cmds, scmd) == FALSE)
			return (0);
	}
	else if (ft_strncmp(scmd->cmd[0], "unset\0", 6) == 0)
		builtin_unset(cmds, scmd);
	else if (ft_strncmp(scmd->cmd[0], "env\0", 4) == 0)
		builtin_env(cmds->env_ll, scmd, cmds);
	else if (ft_strncmp(scmd->cmd[0], "exit\0", 6) == 0)
		builtin_exit(cmds, scmd);
	else
		return (0);
	ft_transfer_ll_to_env_ptr(cmds);
	return (cmds->exit_status);
}
