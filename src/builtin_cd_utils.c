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

int	cd_error_check(t_simple *scmd)
{
	if (scmd->cmd[1] != NULL && scmd->cmd[2])
	{
		print_error("cd: ", NULL, "too many arguments");
		return (FALSE);
	}
	return (TRUE);
}

int	go_back_home(t_simple *scmd)
{
	if (scmd->cmd[1] == NULL)
		return (TRUE);
	else if (ft_strncmp(scmd->cmd[1], "~", 2) == 0)
		return (TRUE);
	else if (ft_strncmp(scmd->cmd[1], "--", 3) == 0)
		return (TRUE);
	return (FALSE);
}

void	update_env_ll_oldpwd(t_compound *cmds)
{
	t_env	*node;

	node = find_node(cmds, "OLDPWD");
	if (node->value)
		free(node->value);
	node->value = NULL;
	node->env_display = FALSE;
}

int	update_oldpwd(t_compound *cmds, char *storage)
{
	t_env	*node;
	char	*dup_pwd;

	node = find_node(cmds, "OLDPWD");
	if (!node)
		return (TRUE);
	node = find_node(cmds, "PWD");
	if (node && node->env_display == 2)
	{
		if (update_env_ll(cmds, "OLDPWD", storage) == FALSE)
			return (print_error(NULL, NULL, strerror(errno)), FALSE);
	}
	else if (!node->value || node->env_display == 3)
		update_env_ll_oldpwd(cmds);
	else if (node->value != NULL || node->env_display < 1)
	{
		dup_pwd = ft_strdup(node->value);
		if (update_env_ll(cmds, "OLDPWD", dup_pwd) == FALSE)
			return (print_error(NULL, NULL, strerror(errno)), free(dup_pwd), 0);
		free(dup_pwd);
	}
	return (TRUE);
}

int	update_pwd(t_compound *cmds, char *new_value)
{
	t_env	*pwd;

	pwd = find_node(cmds, "PWD");
	if (pwd != NULL && pwd->env_display < 2)
	{
		if (update_env_ll(cmds, "PWD", new_value) == FALSE)
			return (print_error(NULL, NULL, strerror(errno)), FALSE);
	}
	return (TRUE);
}
