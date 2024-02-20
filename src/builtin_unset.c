/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2024/02/01 14:29:58 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*Unsetting a variable or function that was not previously set
shall not be considered an error and does not cause the shell to
abort.*/

int	builtin_unset_loop(t_compound *cmds, t_env *haystack, t_env *tmp, char *needle)
{
	while (haystack)
	{
		if (ft_strncmp(haystack->key, needle,
				ft_strlen(haystack->key)) == 0)
		{
			tmp->next = haystack->next;
			haystack->next = NULL;
			ft_free_node(haystack);
			return (0);
		}
		tmp = haystack;
		haystack = haystack->next;
	}
	//if at least one var could not be unset
	//cmds->exit_status = 2;
	return (0);
}

int	builtin_unset(t_compound *cmds, t_simple *scmd)
{
	t_env	*haystack;
	t_env	*tmp;
	char	*needle;
	int		i;

	i = 0;
	needle = NULL;
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
	cmds->exit_status = 0;
	return (cmds->exit_status);
}