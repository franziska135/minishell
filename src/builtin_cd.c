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

int	builtin_cd(t_simple *scmd, t_compound *cmds)
{
	if (cd_error_check(scmd) == FALSE)
		return (set_status(cmds, 1), FALSE);
	else if (go_back_home(scmd) == TRUE)
	{
		if (builtin_cd_home(cmds) == FALSE)
			return (set_status(cmds, 1), FALSE);
	}
	else if (scmd->cmd[1][0] == '\0')
		return (set_status(cmds, 0), TRUE);
	else if (ft_strncmp(scmd->cmd[1], "..\0", 3) == 0)
	{
		if (builtin_cd_dotdot(cmds) == FALSE)
			return (set_status(cmds, 1), FALSE);
	}
	else if (ft_strncmp(scmd->cmd[1], "-", 2) == 0)
	{
		if (builtin_cd_back(cmds) == FALSE)
			return (set_status(cmds, 1), FALSE);
	}
	else
	{
		if (builtin_cd_path(cmds, scmd) == FALSE)
			return (set_status(cmds, 1), FALSE);
	}
	return (set_flag_pwd(cmds), set_status(cmds, 0), TRUE);
}

int	builtin_cd_home(t_compound *cmds)
{
	t_env	*node;
	char	pwd[500];

	node = find_node(cmds, "HOME");
	if (node != NULL && node->value != NULL)
	{
		if (chdir(node->value) == -1)
			return (print_error("cd: ", node->value, strerror(errno)), FALSE);
		if (update_oldpwd(cmds, cmds->pwd) == FALSE)
			return (print_error(NULL, NULL, strerror(errno)), FALSE);
		if (update_pwd(cmds, getcwd(pwd, 500)) == FALSE)
			return (print_error(NULL, NULL, strerror(errno)), FALSE);
	}
	else
	{
		print_error("cd: ", NULL, "HOME not set");
		return (FALSE);
	}
	return (TRUE);
}

int	builtin_cd_dotdot(t_compound *cmds)
{
	char	pwd[100];
	char	*storage;

	storage = getcwd(pwd, 500);
	if (!storage)
		return (print_error("cd: ", "..", strerror(errno)), FALSE);
	if (chdir("..") == -1)
		return (print_error("cd: ", "..: ", strerror(errno)), FALSE);
	if (update_oldpwd(cmds, storage) == FALSE)
		return (print_error(NULL, NULL, strerror(errno)), FALSE);
	if (update_pwd(cmds, getcwd(pwd, 500)) == FALSE)
		return (print_error(NULL, NULL, strerror(errno)), FALSE);
	return (TRUE);
}

int	builtin_cd_back(t_compound *cmds)
{
	char	pwd[100];
	t_env	*node;

	node = find_node(cmds, "OLDPWD");
	if (node != NULL && node->value != NULL)
	{
		if (chdir(node->value) == -1)
			return (print_error("cd: ", node->value, strerror(errno)), FALSE);
		if (update_oldpwd(cmds, cmds->pwd) == FALSE)
			return (print_error(NULL, NULL, strerror(errno)), FALSE);
		if (update_pwd(cmds, getcwd(pwd, 500)) == FALSE)
			return (print_error(NULL, NULL, strerror(errno)), FALSE);
		builtin_pwd(cmds);
	}
	else
	{
		print_error("cd: ", NULL, "OLDPWD not set");
		return (FALSE);
	}
	return (TRUE);
}

int	builtin_cd_path(t_compound *cmds, t_simple *scmd)
{
	char	pwd[500];

	if (chdir(scmd->cmd[1]) == -1)
		return (print_error("cd: ", scmd->cmd[1], strerror(errno)), FALSE);
	if (update_oldpwd(cmds, cmds->pwd) == FALSE)
		return (print_error(NULL, NULL, strerror(errno)), FALSE);
	if (update_pwd(cmds, getcwd(pwd, 500)) == FALSE)
		return (print_error(NULL, NULL, strerror(errno)), FALSE);
	return (TRUE);
}
