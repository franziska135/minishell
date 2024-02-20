/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <zolfagharipour@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:12:28 by mzolfagh          #+#    #+#             */
/*   Updated: 2023/11/27 16:12:30 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dpointer_free(char **str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	struct_free(t_compound cmds)
{
	int		i;

	i = 0;
	while (i < cmds.nbr_scmd)
	{
		dpointer_free(cmds.scmd[i].cmd);
		i++;
	}
	free(cmds.scmd);
}

void	struct_nullifier(t_compound *cmds)
{
	int		i;

	i = 0;
	while (i < cmds->nbr_scmd)
	{
		cmds->scmd[i].cmd = NULL;
		cmds->scmd[i].in_fd = 0;
		cmds->scmd[i].out_fd = 0;
		cmds->scmd[i].builtin = 0;
		i++;
	}
	cmds->nbr_scmd = 0;
}

int	is_built_in(char *str)
{
	if (!str)
		return (FALSE);
	if (!ft_strncmp(str, "cd", 3))
		return (TRUE);
	else if (!ft_strncmp(str, "export", 7))
		return (TRUE);
	else if (!ft_strncmp(str, "unset", 6))
		return (TRUE);
	else if (!ft_strncmp(str, "env", 4))
		return (TRUE);
	else if (!ft_strncmp(str, "exit", 5))
		return (TRUE);
	else if (!ft_strncmp(str, "echo", 5))
		return (TRUE);
	else if (!ft_strncmp(str, "pwd", 4))
		return (TRUE);
	return (FALSE);
}
