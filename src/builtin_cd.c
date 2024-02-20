/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2024/02/20 16:25:43 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//at some point: check if PWd/OLDPWD is updated correctly
//check the buffer size of pwd[]
//find_needle & update blah do NOTHING, if anything is NULL/not found
//but what happens with chdir and getcwd?
//fix what happens if error statement is printed
int	builtin_cd(t_simple *scmd, t_compound *cmds)
{
	if (scmd->cmd[1] != NULL && scmd->cmd[2])
		print_error("cd: ", NULL, "too many arguments");
	else if (scmd->cmd[1] == NULL || ft_strncmp(scmd->cmd[1], "~", 2) == 0)
	{
		if (builtin_cd_home(cmds) == FALSE)
			return (FALSE);
	}
	else if (scmd->cmd[1][0] == '\0')
		return (TRUE);
	else if (ft_strncmp(scmd->cmd[1], "..\0", 3) == 0)
	{
		if (builtin_cd_dotdot(cmds) == FALSE)
			return (FALSE);
	}
	else if (ft_strncmp(scmd->cmd[1], "-", 1) == 0)
	{
		if (builtin_cd_back(cmds) == FALSE)
			return (FALSE);
	}
	else
	{
		if (builtin_cd_path(cmds, scmd) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

//what happens on errors? go back to history promt?
//what's the error if chdir fails?
int	builtin_cd_home(t_compound *cmds)
{
	t_env	*node;
	char	pwd[100];

	node = find_node(cmds, "HOME");
	if (node != NULL && node->value != NULL)
	{
		if (update_env_ll(cmds, "OLDPWD", getcwd(pwd, 100)) == FALSE)
			return (print_error(NULL, NULL, strerror(errno)), FALSE);
		if (chdir(node->value) == -1)
			return (print_error("cd: ", node->value, strerror(errno)), FALSE);
		if (update_env_ll(cmds, "PWD", getcwd(pwd, 100)) == FALSE)
			return (print_error(NULL, NULL, strerror(errno)), FALSE);
	}
	else
		print_error("cd: ", NULL, "HOME not set");
	return (TRUE);
}

//what happens on errors? go back to history promt?
//what's the error if chdir fails?
int	builtin_cd_dotdot(t_compound *cmds)
{
	char	pwd[100];

	if (update_env_ll(cmds, "OLDPWD", getcwd(pwd, 100)) == FALSE)
		return (print_error(NULL, NULL, strerror(errno)), FALSE);
	if (chdir("..") == -1)
		return (print_error("cd: ", "..: ", strerror(errno)), FALSE);
	if (update_env_ll(cmds, "PWD", getcwd(pwd, 100)) == FALSE)
		return (print_error(NULL, NULL, strerror(errno)), FALSE);
	return (TRUE);
}

//what happens on errors? go back to history promt?
//what's the error if chdir fails?
int	builtin_cd_back(t_compound *cmds)
{
	char	pwd[100];
	t_env	*node;
	char	*tmp;

	node = find_node(cmds, "OLDPWD");
	if (node != NULL && node->value != NULL)
	{
		tmp = getcwd(pwd, 100);
		if (chdir(node->value) == -1)
			return (print_error("cd: ", "-: ", strerror(errno)), FALSE);
		if (update_env_ll(cmds, "OLDPWD", tmp) == FALSE)
			return (print_error(NULL, NULL, strerror(errno)), FALSE);
		if (update_env_ll(cmds, "PWD", getcwd(pwd, 100)) == FALSE)
			return (print_error(NULL, NULL, strerror(errno)), FALSE);
		builtin_pwd();
	}
	else
		print_error("cd: ", NULL, "OLDPWD not set");
	return (TRUE);
}

int	builtin_cd_path(t_compound *cmds, t_simple *scmd)
{
	t_env	*node;
	char	pwd[100];
	char	*tmp;

	tmp = getcwd(pwd, 100);
	if (!tmp)
	{
		set_status(cmds, 1);
		print_error("cd: ", scmd->cmd[1], strerror(errno));
		return (0);
	}
	if (chdir(scmd->cmd[1]) == -1)
	{
		set_status(cmds, 1);
		print_error("cd: ", scmd->cmd[1], strerror(errno));
		return (0);
	}
	else
	{
		if (update_env_ll(cmds, "OLDPWD", tmp) == FALSE)
			return (print_error(NULL, NULL, strerror(errno)), FALSE);
		if (update_env_ll(cmds, "PWD", getcwd(pwd, 100)) == FALSE)
			return (print_error(NULL, NULL, strerror(errno)), FALSE);
	}
	return (TRUE);
}
