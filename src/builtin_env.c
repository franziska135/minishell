/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2024/02/20 16:26:00 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(t_env *head, t_simple *scmd, t_compound *cmds)
{
	t_env	*current;

	current = head;
	if (scmd->cmd[1])
	{
		print_error(NULL, scmd->cmd[1], "No such file or directory");
		set_status(cmds, 127);
		return ;
	}
	while (current)
	{
		if (current->env_display == TRUE)
		{
			write(1, current->key, ft_strlen(current->key));
			write (1, "=", 1);
			if (current->value)
				write(1, current->value, ft_strlen(current->value));
			write (1, "\n", 1);
		}
		current = current->next;
	}
	set_status(cmds, 0);
}
