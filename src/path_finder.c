/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <zolfagharipour@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:12:28 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/02/20 18:15:05 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*path_access(t_compound *cmds, char *path, char *cmd)
{
	char	**path_split;
	char	*tmp;
	int		j;

	path_split = ft_split(path, ':');
	if (!path_split)
		return (NULL);
	j = 0;
	while (path_split[j])
	{
		tmp = ft_strjoin(path_split[j], "/");
		if (!tmp)
			return (dpointer_free(path_split), NULL);
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!path)
			return (dpointer_free(path_split), NULL);
		if (!access(path, F_OK | X_OK))
			return (dpointer_free(path_split), path);
		free(path);
		j++;
	}
	dpointer_free(path_split);
	(write(2, cmd, ft_strlen(cmd)), write(2, ": command not found\n", 21));
	return (NULL);
}

int	isit_path(char *str)
{
	while (*str)
	{
		if (*str == '/')
			return (1);
		str++;
	}
	return (0);
}

char	*path_finder(t_compound *cmds, int pipe)
{
	t_env	*env;

	if (!cmds->scmd[pipe].cmd[0])
		return (NULL);
	if (!cmds->scmd[pipe].cmd[0][0])
	{
		print_error(NULL, "''", "command not found");
		return (NULL);
	}
	if (!access(cmds->scmd[pipe].cmd[0], F_OK | X_OK))
		return (cmds->scmd[pipe].cmd[0]);
	if (isit_path(cmds->scmd[pipe].cmd[0]))
	{
		print_error(NULL, cmds->scmd[pipe].cmd[0], "No such file or directory");
		return (NULL);
	}
	env = find_node(cmds, "PATH");
	if (env && env->value)
		return (path_access(cmds, env->value, cmds->scmd[pipe].cmd[0]));
	return (NULL);
}
