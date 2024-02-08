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
void	builtin_unset(t_compound *cmds, t_simple *scmd)
{
	t_env	*haystack;
	t_env	*tmp;
	char	*needle;

	needle = NULL;
	if (scmd->cmd[1])
		needle = scmd->cmd[1];
	haystack = cmds->env_ll;
	if (needle)
	{
		while (haystack)
		{
			if (ft_strncmp(haystack->key, needle,
					ft_strlen(haystack->key)) == 0)
			{
				tmp->next = haystack->next;
				haystack->next = NULL;
				write(1, haystack->key, ft_strlen(haystack->key));
				//write (1, " is now unset\n", 14);
				ft_free_node(haystack);
				return ;
			}
			tmp = haystack;
			haystack = haystack->next;
		}
		//write (1, "variable not found\n", 19);
	}
}
