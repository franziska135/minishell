/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2024/02/20 16:25:35 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_path_unset(t_compound *cmds, char *needle)
{
	t_env	*node;

	if (ft_strncmp(needle, "PWD", 4) == 0)
	{
		node = find_node(cmds, needle);
		if (!node)
			return (FALSE);
		if (node->env_display < 2)
			node->env_display = 3;
		if (node->value)
			free(node->value);
		node->value = NULL;
		return (TRUE);
	}
	return (FALSE);
}

int	builtin_unset_loop(t_compound *cmds, t_env *hay, t_env *tmp, char *needle)
{
	if (pwd_path_unset(cmds, needle) == TRUE)
		return (1);
	if (hay && ft_strncmp(hay->key, needle, ft_strlen(hay->key)) == 0)
	{
		cmds->env_ll = hay->next;
		hay->next = NULL;
		ft_free_node(hay);
		return (0);
	}
	while (hay)
	{
		if (ft_strncmp(hay->key, needle, ft_strlen(needle) + 1) == 0)
		{
			tmp->next = hay->next;
			hay->next = NULL;
			ft_free_node(hay);
			return (0);
		}
		tmp = hay;
		hay = hay->next;
	}
	return (0);
}

int	builtin_unset(t_compound *cmds, t_simple *scmd)
{
	t_env	*haystack;
	t_env	*tmp;
	int		i;

	i = 1;
	tmp = NULL;
	if (!scmd->cmd[1])
		return (set_status(cmds, 0), 0);
	if (scmd->cmd[1][0] == '-' && scmd->cmd[1][1])
	{
		(write(1, "bash : unset: -", 15)), (write(1, &scmd->cmd[1][1], 1));
		write(1, ": invalid option\n", 17);
		return (set_status(cmds, 2), 2);
	}
	while (scmd->cmd[i])
	{
		haystack = cmds->env_ll;
		if (scmd->cmd[i])
			builtin_unset_loop(cmds, haystack, tmp, scmd->cmd[i]);
		i++;
	}
	set_status(cmds, 0);
	return (cmds->exit_status);
}
